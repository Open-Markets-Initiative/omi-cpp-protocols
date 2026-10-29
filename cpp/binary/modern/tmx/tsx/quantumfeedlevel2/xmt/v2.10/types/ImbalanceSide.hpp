#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {


// Marker To Indicate Which Side Has An Imbalance Volume For Market On Close
struct ImbalanceSide {

    static constexpr auto name = "Imbalance Side";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ImbalanceSide()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ImbalanceSide(const char &value)
     : value{ value } {}

    // get value of ImbalanceSide field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
