#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// The side of this individual leg (multileg security). See Side (54) field for description and values.
struct LegSide {

    static constexpr auto name = "Leg Side";
    static constexpr std::size_t size = 1;
    using type = char;
static const type no_value = '0';

    // default constructor
    constexpr LegSide()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegSide(const char &value)
     : value{ value } {}

    // get value of LegSide field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
