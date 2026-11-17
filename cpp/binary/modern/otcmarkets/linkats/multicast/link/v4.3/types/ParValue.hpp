// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/ParValue.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Par value with 6 decimal places assumed. 0 indicates not available.
struct ParValue {

    static constexpr const char* name = "Par Value";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr ParValue()
     : value{ 0 } {}

    // constructor for ParValue field
    constexpr explicit ParValue(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ParValue field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ParValue field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
