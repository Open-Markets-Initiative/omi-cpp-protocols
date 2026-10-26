#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {


// priceBandType
struct PriceBandType {

    static constexpr auto name = "Price Band Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr PriceBandType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceBandType(const std::uint8_t &value)
     : value{ value } {}

    // get value of PriceBandType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
