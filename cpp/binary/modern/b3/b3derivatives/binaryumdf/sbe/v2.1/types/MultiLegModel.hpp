#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {


// multiLegModel
struct MultiLegModel {

    static constexpr auto name = "Multi Leg Model";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr MultiLegModel()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MultiLegModel(const std::uint8_t &value)
     : value{ value } {}

    // get value of MultiLegModel field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
