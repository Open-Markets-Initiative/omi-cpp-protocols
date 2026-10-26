#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The display ask price of the new quote. NOTE: When converted to a decimal format, this price is in fixed point format with 3 whole number places followed by 2 decimal digits.
struct AskPriceShort {

    static constexpr const char* name = "Ask Price Short";
    static constexpr std::size_t size =  2;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint16_t;

    // default constructor
    constexpr AskPriceShort()
     : value{ 0 } {}

    // constructor for AskPriceShort field
    constexpr explicit AskPriceShort(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of AskPriceShort field
    [[nodiscard]] std::uint16_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of AskPriceShort field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint16_t value;
};
}
