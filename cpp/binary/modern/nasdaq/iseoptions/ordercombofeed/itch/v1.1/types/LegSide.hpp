#pragma once

#include <cstddef>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {


// Indicates the side of the leg
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
