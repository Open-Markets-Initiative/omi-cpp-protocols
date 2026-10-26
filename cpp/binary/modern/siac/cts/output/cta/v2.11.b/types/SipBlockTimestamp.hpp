#pragma once

#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Cta packet timestamp
struct SipBlockTimestamp {

    static constexpr const char* name = "SIP Block Timestamp";
    static constexpr std::size_t size = 8;

    // underlying composed type (epoch nanoseconds)
    using type = std::uint64_t;

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
