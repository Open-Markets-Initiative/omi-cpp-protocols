#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {


// priceLimitType
struct PriceLimitType {

    static constexpr auto name = "Price Limit Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr PriceLimitType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceLimitType(const std::uint8_t &value)
     : value{ value } {}

    // get value of PriceLimitType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
