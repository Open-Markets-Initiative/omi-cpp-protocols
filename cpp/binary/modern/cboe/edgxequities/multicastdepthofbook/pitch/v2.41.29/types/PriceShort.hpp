#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29 {

// The limit order price
struct PriceShort {

    static constexpr const char* name = "Price Short";
    static constexpr std::size_t size =  2;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::uint16_t;

    // default constructor
    constexpr PriceShort()
     : value{ 0 } {}

    // constructor for PriceShort field
    constexpr explicit PriceShort(const std::uint16_t value)
     : value{ value } {}

    // get underlying integer of PriceShort field
    [[nodiscard]] std::uint16_t integer() const {
        return value;
    }

    // decimal value of PriceShort field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint16_t value;
};
}
