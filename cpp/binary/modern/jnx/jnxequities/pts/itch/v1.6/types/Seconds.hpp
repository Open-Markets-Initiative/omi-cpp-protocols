#pragma once

#include <bit>
#include <chrono>
#include <cstddef>
#include <cstdint>

#include "../common/Day.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

// Number of seconds since midnight of the day that the trading session started.
struct Seconds {

    using type = std::uint32_t;

    static constexpr const char* name = "Seconds";
    static constexpr std::size_t size = 4;

    // default constructor
    constexpr Seconds()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Seconds(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of Seconds field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

    // trading-day midnight (Asia/Tokyo) from the capture time, plus this stored second: the
    // zone's offset at that day's midnight, daylight saving included
    [[nodiscard]] std::int64_t midnight(const std::int64_t capture_ns) const {
        static const std::chrono::time_zone* const zone = std::chrono::locate_zone("Asia/Tokyo");
        const std::chrono::sys_seconds capture{ std::chrono::floor<std::chrono::seconds>(std::chrono::nanoseconds{ capture_ns }) };
        const auto day = std::chrono::floor<std::chrono::days>(zone->to_local(capture));
        const auto midnight = zone->to_sys(day, std::chrono::choose::earliest);
        return (midnight.time_since_epoch().count() + static_cast<std::int64_t>(get())) * 1000000000;
    }

    // Seconds on a day: its seconds since midnight, Asia/Tokyo, as UTC Unix nanoseconds
    [[nodiscard]] std::int64_t utc(const calendar::Day& day) const {
        return calendar::midnight(day, "Asia/Tokyo").utc(static_cast<std::int64_t>(get()) * 1000000000);
    }

  protected:
    std::uint32_t value;
};
}
