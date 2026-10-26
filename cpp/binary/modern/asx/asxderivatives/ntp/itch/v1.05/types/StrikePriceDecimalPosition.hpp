#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {


// Number of decimals to display the strike price.
struct StrikePriceDecimalPosition {

    static constexpr auto name = "Strike Price Decimal Position";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr StrikePriceDecimalPosition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StrikePriceDecimalPosition(const std::uint8_t &value)
     : value{ value } {}

    // get value of StrikePriceDecimalPosition field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
