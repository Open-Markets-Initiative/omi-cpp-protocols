#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {


// priceType
struct PriceType {

    static constexpr auto name = "Price Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr PriceType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceType(const std::uint8_t &value)
     : value{ value } {}

    // get value of PriceType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
