#pragma once

#include <bit>
#include <chrono>
#include <cstddef>
#include <cstdint>

#include "../common/Day.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// Number of seconds since midnight.
struct Second {

    using type = std::uint32_t;

    static constexpr const char* name = "Second";
    static constexpr std::size_t size = 4;

    // default constructor
    constexpr Second()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Second(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of Second field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

    // trading-day midnight (America/New_York) from the capture time, plus this stored second: the
    // zone's offset at that day's midnight, daylight saving included
    [[nodiscard]] std::int64_t midnight(const std::int64_t capture_ns) const {
        static const std::chrono::time_zone* const zone = std::chrono::locate_zone("America/New_York");
        const std::chrono::sys_seconds capture{ std::chrono::floor<std::chrono::seconds>(std::chrono::nanoseconds{ capture_ns }) };
        const auto day = std::chrono::floor<std::chrono::days>(zone->to_local(capture));
        const auto midnight = zone->to_sys(day, std::chrono::choose::earliest);
        return (midnight.time_since_epoch().count() + static_cast<std::int64_t>(get())) * 1000000000;
    }

    // Second on a day: its seconds since midnight, America/New_York, as UTC Unix nanoseconds
    [[nodiscard]] std::int64_t utc(const calendar::Day& day) const {
        return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(get()) * 1000000000);
    }

  protected:
    std::uint32_t value;
};
}
