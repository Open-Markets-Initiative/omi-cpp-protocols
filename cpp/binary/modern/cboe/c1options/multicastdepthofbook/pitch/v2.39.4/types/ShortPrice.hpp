#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// The limit order price
struct ShortPrice {

    static constexpr const char* name = "Short Price";
    static constexpr std::size_t size =  2;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::uint16_t;

    // default constructor
    constexpr ShortPrice()
     : value{ 0 } {}

    // constructor for ShortPrice field
    constexpr explicit ShortPrice(const std::uint16_t value)
     : value{ value } {}

    // get underlying integer of ShortPrice field
    [[nodiscard]] std::uint16_t integer() const {
        return value;
    }

    // decimal value of ShortPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint16_t value;
};
}
