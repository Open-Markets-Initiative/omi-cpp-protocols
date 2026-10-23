#pragma once

#include <cstddef>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// Leg side. This field will repeat for each leg.
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
