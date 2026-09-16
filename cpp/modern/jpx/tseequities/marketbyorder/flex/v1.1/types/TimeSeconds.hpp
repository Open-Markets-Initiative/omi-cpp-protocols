#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Set to UNIX time (seconds since 1970-01-01 00:00:00 UTC)
struct TimeSeconds {

    using type = std::uint32_t;

    static constexpr const char* name = "Time Seconds";
    static constexpr std::size_t size = 4;

    // default constructor
    constexpr TimeSeconds()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TimeSeconds(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of TimeSeconds field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

    // trading-day midnight (UTC) from the capture time, plus this stored second
    [[nodiscard]] std::int64_t midnight(const std::int64_t capture_ns) const {
        constexpr std::int64_t timezone_offset = 0;
        constexpr std::int64_t day = 86400;
        const std::int64_t local = capture_ns / 1000000000 + timezone_offset;
        return (local - ((local % day + day) % day) - timezone_offset + static_cast<std::int64_t>(get())) * 1000000000;
    }

  protected:
    std::uint32_t value;
};
}
