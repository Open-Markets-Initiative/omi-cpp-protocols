#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {


// Resulting number of splits at the previous price Defaulted to 0. Future use by NYSE only.
struct PrevPriceParitySplits {

    static constexpr auto name = "Prev Price Parity Splits";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr PrevPriceParitySplits()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PrevPriceParitySplits(const std::uint8_t &value)
     : value{ value } {}

    // get value of PrevPriceParitySplits field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
