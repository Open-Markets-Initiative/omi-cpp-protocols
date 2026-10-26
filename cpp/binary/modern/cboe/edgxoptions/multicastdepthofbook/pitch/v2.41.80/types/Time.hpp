#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>

#include "../common/Day.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// Number of whole seconds elapsed since the start of the current Eastern Time calendar day, derived by converting the current Eastern wall clock time (HH:MM:SS) to seconds. On Daylight Saving Time transition days, Time reflects wall clock seconds and does not adjust for the UTC offset change. On a DST spring-forward day, the maximum value will be 82,799 (23 hours). On a DST fall-back day, values between 3,600 and 7,199 will appear twice. Recipients requiring unambiguous absolute timestamps should use Epoch Time (where available) or Midnight Reference in the Time Reference message.
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
