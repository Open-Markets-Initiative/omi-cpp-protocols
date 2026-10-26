#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {


// Suggested number of decimals to display the price at.
struct PriceDisplayDecimals {

    static constexpr auto name = "Price Display Decimals";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr PriceDisplayDecimals()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceDisplayDecimals(const std::uint8_t &value)
     : value{ value } {}

    // get value of PriceDisplayDecimals field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
