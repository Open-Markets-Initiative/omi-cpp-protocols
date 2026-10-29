#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>

#include "../common/Day.hpp"

namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29 {

// Number of whole seconds from midnight Eastern Time
struct Time {

    static constexpr const char* name = "Time";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Time()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Time(const std::uint32_t value)
     : value{ value } {}

    // get value of Time field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

    // Time on a day: its seconds since midnight, America/New_York, as UTC Unix nanoseconds
    [[nodiscard]] std::int64_t utc(const calendar::Day& day) const {
        return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(get()) * 1000000000);
    }

  protected:
    std::uint32_t value;
};
}
