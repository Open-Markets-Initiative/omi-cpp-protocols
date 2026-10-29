#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>

#include "../common/Day.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// Number of seconds since midnight. Midnight will be in terms of the local time for the server (i.e. not UTC).
struct Seconds {

    static constexpr const char* name = "Seconds";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Seconds()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Seconds(const std::uint32_t value)
     : value{ value } {}

    // get value of Seconds field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

    // Seconds on a day: its seconds since midnight, Europe/London, as UTC Unix nanoseconds
    [[nodiscard]] std::int64_t utc(const calendar::Day& day) const {
        return calendar::midnight(day, "Europe/London").utc(static_cast<std::int64_t>(get()) * 1000000000);
    }

  protected:
    std::uint32_t value;
};
}
