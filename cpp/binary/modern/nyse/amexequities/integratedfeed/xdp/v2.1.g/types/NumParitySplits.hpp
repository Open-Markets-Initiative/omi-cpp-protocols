#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {


// Resulting number of splits at this price level Defaulted to 0. Future use by NYSE only.
struct NumParitySplits {

    static constexpr auto name = "Num Parity Splits";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NumParitySplits()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumParitySplits(const std::uint8_t &value)
     : value{ value } {}

    // get value of NumParitySplits field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
