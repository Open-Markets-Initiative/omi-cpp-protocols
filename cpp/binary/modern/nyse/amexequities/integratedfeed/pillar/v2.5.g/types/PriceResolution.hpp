#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexequities::integratedfeed::pillar::v2_5_g {


// Minimum price increment: 0 - All Penny, 1 - Penny/Nickel, 5 - Nickel/Dime.
struct PriceResolution {

    static constexpr auto name = "Price Resolution";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr PriceResolution()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceResolution(const std::uint8_t &value)
     : value{ value } {}

    // get value of PriceResolution field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
