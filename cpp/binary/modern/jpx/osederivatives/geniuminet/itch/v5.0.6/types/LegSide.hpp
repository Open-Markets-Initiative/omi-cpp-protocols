#pragma once

#include <cstddef>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {


// Leg Side
struct LegSide {

    static constexpr auto name = "Leg Side";
    static constexpr std::size_t size = 1;

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
