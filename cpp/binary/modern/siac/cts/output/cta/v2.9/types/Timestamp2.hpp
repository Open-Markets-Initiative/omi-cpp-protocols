#pragma once

#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_9 {

// Timestamp 2
struct Timestamp2 {

    static constexpr const char* name = "Timestamp 2";
    static constexpr std::size_t size = 8;

    // underlying composed type (epoch nanoseconds)
    using type = std::uint64_t;
static const type no_value = 0;

    // epoch nanoseconds composed from the little-endian Seconds + Nanoseconds parts
    [[nodiscard]] std::uint64_t get() const {
        return static_cast<std::uint64_t>(seconds) * 1'000'000'000ULL + nanoseconds;
    }

  protected:
    // little-endian on the wire = native on x86; overlays the 8 field bytes
    std::uint32_t seconds;
    std::uint32_t nanoseconds;
};
}
