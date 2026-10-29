#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Best ask price in fixed point format with 6 whole number places followed by 4 decimal digits.
struct AskPrice {

    static constexpr const char* name = "Ask Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int32_t;

    // default constructor
    constexpr AskPrice()
     : value{ 0 } {}

    // constructor for AskPrice field
    constexpr explicit AskPrice(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of AskPrice field
    [[nodiscard]] std::int32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of AskPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int32_t value;
};
}
