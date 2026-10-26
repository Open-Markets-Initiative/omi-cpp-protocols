#pragma once

#include <cstddef>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// Leg Security Type. This field will repeat for each leg.
struct LegSecurityType {

    static constexpr auto name = "Leg Security Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr LegSecurityType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegSecurityType(const char &value)
     : value{ value } {}

    // get value of LegSecurityType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
