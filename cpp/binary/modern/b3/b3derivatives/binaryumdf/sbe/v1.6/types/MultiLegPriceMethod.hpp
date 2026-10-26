#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {


// multiLegPriceMethod
struct MultiLegPriceMethod {

    static constexpr auto name = "Multi Leg Price Method";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr MultiLegPriceMethod()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MultiLegPriceMethod(const std::uint8_t &value)
     : value{ value } {}

    // get value of MultiLegPriceMethod field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
