// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/SpinStartTimeMilli.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Milliseconds since UTC epoch.
struct SpinStartTimeMilli {

    static constexpr const char* name = "Spin Start Time Milli";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr SpinStartTimeMilli()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SpinStartTimeMilli(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of SpinStartTimeMilli field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
