#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

// The limit order price
struct PriceBinaryShortPrice2 {

    static constexpr const char* name = "Price Binary Short Price 2";
    static constexpr std::size_t size =  2;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::uint16_t;

    // default constructor
    constexpr PriceBinaryShortPrice2()
     : value{ 0 } {}

    // constructor for PriceBinaryShortPrice2 field
    constexpr explicit PriceBinaryShortPrice2(const std::uint16_t value)
     : value{ value } {}

    // get underlying integer of PriceBinaryShortPrice2 field
    [[nodiscard]] std::uint16_t integer() const {
        return value;
    }

    // decimal value of PriceBinaryShortPrice2 field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint16_t value;
};
}
