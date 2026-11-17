// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/SpinEndTimeMilli.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Milliseconds since UTC epoch.
struct SpinEndTimeMilli {

    static constexpr const char* name = "Spin End Time Milli";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr SpinEndTimeMilli()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SpinEndTimeMilli(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of SpinEndTimeMilli field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
