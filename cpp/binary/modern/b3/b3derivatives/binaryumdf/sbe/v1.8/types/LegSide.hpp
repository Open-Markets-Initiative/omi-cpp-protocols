#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {


// Side of this leg.
struct LegSide {

    static constexpr auto name = "Leg Side";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr LegSide()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegSide(const std::uint8_t &value)
     : value{ value } {}

    // get value of LegSide field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
