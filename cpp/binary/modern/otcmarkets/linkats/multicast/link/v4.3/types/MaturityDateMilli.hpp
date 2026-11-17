// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/MaturityDateMilli.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Maturity date in milliseconds from UTC epoch. Applies to fixed income securities only.
struct MaturityDateMilli {

    static constexpr const char* name = "Maturity Date Milli";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr MaturityDateMilli()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MaturityDateMilli(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of MaturityDateMilli field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
