#pragma once

#include <bit>
#include <chrono>
#include <cstddef>
#include <cstdint>

#include "../common/Day.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Number of nanoseconds past midnight of the current calendar date
struct Timestamp {

    static constexpr const char* name = "Timestamp";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr Timestamp()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Timestamp(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of Timestamp field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

    // Timestamp on a day: its nanoseconds since midnight, Asia/Tokyo, as UTC Unix nanoseconds
    [[nodiscard]] std::int64_t utc(const calendar::Day& day) const {
        return calendar::midnight(day, "Asia/Tokyo").utc(static_cast<std::int64_t>(get()));
    }

  protected:
    std::uint64_t value;
};
}
