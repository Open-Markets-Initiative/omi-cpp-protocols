#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Denominator of the price to yield the floating point price.
struct PriceFractionalDenominator {

    static constexpr const char* name = "Price Fractional Denominator";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr PriceFractionalDenominator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceFractionalDenominator(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of PriceFractionalDenominator field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
