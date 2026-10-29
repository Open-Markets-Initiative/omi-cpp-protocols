#pragma once

#include <cstddef>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {


// Spread Type
struct SpreadType {

    static constexpr auto name = "Spread Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SpreadType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SpreadType(const char &value)
     : value{ value } {}

    // get value of SpreadType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
