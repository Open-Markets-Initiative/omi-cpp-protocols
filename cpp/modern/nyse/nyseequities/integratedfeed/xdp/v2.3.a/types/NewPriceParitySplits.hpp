#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {


// Resulting number of splits at the new price. Defaulted to 0. Future use by NYSE only.
struct NewPriceParitySplits {

    static constexpr auto name = "New Price Parity Splits";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NewPriceParitySplits()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NewPriceParitySplits(const std::uint8_t &value)
     : value{ value } {}

    // get value of NewPriceParitySplits field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
