#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Denominator of the Strike Price to yield the floating point strike price.
struct StrikePriceFractionalDenominator {

    static constexpr const char* name = "Strike Price Fractional Denominator";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr StrikePriceFractionalDenominator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StrikePriceFractionalDenominator(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of StrikePriceFractionalDenominator field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
