#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// Best ask price. NOTE: When converted to a decimal format, the price is in fixed point format with 3 whole number places followed by 2 decimal digits.
struct AskPrice2 {

    static constexpr const char* name = "Ask Price 2";
    static constexpr std::size_t size =  2;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::uint16_t;

    // default constructor
    constexpr AskPrice2()
     : value{ 0 } {}

    // constructor for AskPrice2 field
    constexpr explicit AskPrice2(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of AskPrice2 field
    [[nodiscard]] std::uint16_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of AskPrice2 field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint16_t value;
};
}
