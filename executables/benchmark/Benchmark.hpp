#pragma once

// The benchmark harness: a capture held in memory, every datagram read once before anything is timed,
// the reading warmed up, then sampled - each sample whole passes over the capture, long enough for the
// clock to resolve - until enough samples and enough time are in hand to trust them. A pass is the
// format reading every value of every message of every datagram, each folded into a checksum the
// compiler must keep, and every pass must come to the same checksum. The spread of the samples is
// reported, not only the best of them.

#include <algorithm>
#include <bit>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iterator>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#if defined(__linux__)
#include <sched.h>
#endif

#include "PcapIterator.hpp"
#include "Frame.hpp"

namespace bench {

using clock = std::chrono::steady_clock;

// A value folded into the checksum, whatever its type: a number as itself, a duration or a time as its
// ticks, a value that may be absent as what it holds or nothing, text as its length and first character
template <typename T>
std::uint64_t digest(const T& value) {
    using V = std::remove_cvref_t<T>;

    if constexpr (std::is_enum_v<V>) {
        return static_cast<std::uint64_t>(std::to_underlying(value));
    } else if constexpr (std::is_same_v<V, bool>) {
        return value ? 1u : 0u;
    } else if constexpr (std::is_integral_v<V>) {
        return static_cast<std::uint64_t>(value);
    } else if constexpr (std::is_floating_point_v<V>) {
        return std::bit_cast<std::uint64_t>(static_cast<double>(value));
    } else if constexpr (requires { value.time_since_epoch(); }) {
        return digest(value.time_since_epoch());
    } else if constexpr (requires { value.count(); }) {
        return static_cast<std::uint64_t>(value.count());
    } else if constexpr (requires { value.has_value(); *value; }) {
        return value.has_value() ? digest(*value) : 0u;
    } else if constexpr (requires { std::size(value); std::data(value); }) {
        const auto size = static_cast<std::uint64_t>(std::size(value));
        return size == 0 ? 0u : size + static_cast<unsigned char>(std::data(value)[0]);
    } else {
        static_assert(sizeof(V) == 0, "bench::digest does not fold a value of this type");
    }
}

// Keep a checksum, and every read making it, from being optimized away
inline void keep(std::uint64_t value) {
#if defined(__GNUC__) || defined(__clang__)
    asm volatile("" : : "r"(value) : "memory");
#else
    static volatile std::uint64_t kept;
    kept = value;
#endif
}

// Pin the process to the CPU it runs on, so the samples are not spread over cores; -1 where it cannot be
inline int pin() {
#if defined(__linux__)
    const int cpu = sched_getcpu();
    cpu_set_t set;
    CPU_ZERO(&set);

    if (cpu >= 0) {
        CPU_SET(cpu, &set);
        if (sched_setaffinity(0, sizeof(set), &set) == 0) {
            return cpu;
        }
    }
#endif
    return -1;
}

// A capture's UDP frames, held in memory: each frame's bytes copied once, untimed, and a frame over them
class Capture {
  public:
    explicit Capture(const std::string& path) {
        std::vector<std::pair<std::string, std::int64_t>> sources;
        sources.emplace_back(path, 0);
        packet::PcapIterator captures(sources);

        while (captures.advance()) {
            const auto length = static_cast<std::uint32_t>(captures.length());
            const packet::Frame frame(captures.data(), length);

            if (frame.valid() && frame.is_udp()) {
                bytes_.emplace_back(captures.data(), captures.data() + length);
            }
        }

        for (const auto& each : bytes_) {
            frames_.emplace_back(each.data(), static_cast<std::uint32_t>(each.size()));
            payload_ += frames_.back().payload_len;
        }
    }

    const std::vector<packet::Frame>& frames() const { return frames_; }
    std::size_t payload() const { return payload_; }

  private:
    std::vector<std::vector<std::byte>> bytes_;
    std::vector<packet::Frame> frames_;
    std::size_t payload_ = 0;
};

// The spread of the samples, each in nanoseconds per datagram
struct Spread {
    double least = 0;
    double median = 0;
    double p90 = 0;
    double p99 = 0;
    double mean = 0;
};

inline double nanoseconds(clock::duration took) {
    return std::chrono::duration<double, std::nano>(took).count();
}

inline Spread spread(std::vector<double> samples) {
    std::sort(samples.begin(), samples.end());

    const auto at = [&](double quantile) {
        return samples[static_cast<std::size_t>(quantile * static_cast<double>(samples.size() - 1) + 0.5)];
    };

    double total = 0;
    for (const double sample : samples) { total += sample; }

    return { samples.front(), at(0.5), at(0.9), at(0.99), total / static_cast<double>(samples.size()) };
}

// How long the samples are taken for, at least, and how many at least
constexpr double default_seconds = 1.0;
constexpr std::size_t least_samples = 30;

// Each sample lasts at least this long, far above the clock's resolution
constexpr double least_sample_ns = 20'000;

// Time a format's reading of a capture: argv[1] the capture, argv[2] the seconds to sample for. It
// passes only where every datagram reads, and reads the same every time.
template <typename Read>
int run(const char* protocol, const char* format, int argc, char** argv, Read read) {
    if (argc < 2) {
        std::fprintf(stderr, "usage: %s <capture.pcap> [seconds]\n", argv[0]);
        return 2;
    }

    const double seconds = argc > 2 ? std::max(0.001, std::atof(argv[2])) : default_seconds;
    const int cpu = pin();

    std::printf("== %s (%s benchmark)\n", protocol, format);

    std::vector<packet::Frame> frames;
    std::size_t payload = 0;

    try {
        const Capture capture(argv[1]);
        frames = capture.frames();
        payload = capture.payload();

        if (frames.empty()) {
            std::printf("FAIL: %s holds no UDP datagram\n", argv[1]);
            return 1;
        }

        // every datagram must read before any is timed
        std::uint64_t expected = 0;

        for (std::size_t index = 0; index < frames.size(); ++index) {
            try {
                expected += read(frames[index]);
            } catch (const std::exception& error) {
                std::printf("FAIL: datagram %zu does not read: %s\n", index, error.what());
                return 1;
            }
        }

        const auto pass = [&] {
            std::uint64_t checksum = 0;
            for (const auto& frame : frames) { checksum += read(frame); }
            return checksum;
        };

        // warmed up, and how many passes make a sample long enough to resolve
        std::size_t batch = 1;
        const auto warming = clock::now();

        while (true) {
            const auto start = clock::now();
            for (std::size_t index = 0; index < batch; ++index) { keep(pass()); }
            const double took = nanoseconds(clock::now() - start);

            if (took >= least_sample_ns && nanoseconds(clock::now() - warming) >= seconds * 1e8) { break; }
            if (took < least_sample_ns) { batch *= 2; }
        }

        const double warmed = nanoseconds(clock::now() - warming) / 1e9;

        // the samples, each a batch of passes, every pass held to the checksum the first read came to
        std::vector<double> samples;
        const auto sampling = clock::now();

        while (samples.size() < least_samples || nanoseconds(clock::now() - sampling) < seconds * 1e9) {
            std::uint64_t checksum = 0;
            const auto start = clock::now();
            // kept after every pass: no pass can be worked out once for the batch
            for (std::size_t index = 0; index < batch; ++index) { checksum += pass(); keep(checksum); }
            const double took = nanoseconds(clock::now() - start);

            if (checksum != expected * batch) {
                std::printf("FAIL: a pass read other than the first read did\n");
                return 1;
            }

            samples.push_back(took / static_cast<double>(batch * frames.size()));
        }

        const auto per = spread(samples);
        const double sampled = nanoseconds(clock::now() - sampling) / 1e9;

        std::printf("  %zu datagrams, %zu bytes, checksum %016llx\n", frames.size(), payload, static_cast<unsigned long long>(expected));
        std::printf("  %zu samples of %zu passes over %.2f s, after %.2f s warming up, %s",
            samples.size(), batch, sampled, warmed, cpu >= 0 ? "pinned to CPU " : "not pinned\n");
        if (cpu >= 0) { std::printf("%d\n", cpu); }
        std::printf("  per datagram: least %.1f ns, median %.1f ns, p90 %.1f ns, p99 %.1f ns, mean %.1f ns\n",
            per.least, per.median, per.p90, per.p99, per.mean);
        std::printf("  at the median: %.2f M datagrams/s, %.1f MB/s\n",
            1e3 / per.median, static_cast<double>(payload) / static_cast<double>(frames.size()) / per.median * 1e3);
#ifndef NDEBUG
        std::printf("  (built without NDEBUG: these are the timings of a build that may not be optimized)\n");
#endif
    } catch (const std::exception& error) {
        std::printf("FAIL: %s\n", error.what());
        return 1;
    }

    std::printf("PASS\n");
    return 0;
}

}