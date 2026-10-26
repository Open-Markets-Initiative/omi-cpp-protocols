#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {


// priceBandMidpointPriceType
struct PriceBandMidpointPriceType {

    static constexpr auto name = "Price Band Midpoint Price Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr PriceBandMidpointPriceType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceBandMidpointPriceType(const std::uint8_t &value)
     : value{ value } {}

    // get value of PriceBandMidpointPriceType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
