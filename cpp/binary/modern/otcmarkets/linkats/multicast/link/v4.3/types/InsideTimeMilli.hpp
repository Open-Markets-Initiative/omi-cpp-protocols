// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/InsideTimeMilli.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Inside timestamp in milliseconds from UTC epoch.
struct InsideTimeMilli {

    static constexpr const char* name = "Inside Time Milli";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr InsideTimeMilli()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit InsideTimeMilli(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of InsideTimeMilli field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
