// B3.B3Derivatives.BinaryUmdf.Sbe.v2.2: types/Week.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {


// week
struct Week {

    static constexpr auto name = "Week";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0;

    // default constructor
    constexpr Week()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Week(const std::uint8_t &value)
     : value{ value } {}

    // get value of Week field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
