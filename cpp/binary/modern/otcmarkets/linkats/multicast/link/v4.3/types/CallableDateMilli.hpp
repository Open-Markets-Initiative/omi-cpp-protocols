// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/CallableDateMilli.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Callable date in milliseconds from UTC epoch. Applies to fixed income securities only.
struct CallableDateMilli {

    static constexpr const char* name = "Callable Date Milli";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr CallableDateMilli()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CallableDateMilli(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of CallableDateMilli field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
