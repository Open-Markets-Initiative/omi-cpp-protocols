// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/TimeMilli.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Timestamp in milliseconds from UTC epoch.
struct TimeMilli {

    static constexpr const char* name = "Time Milli";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr TimeMilli()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TimeMilli(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of TimeMilli field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
