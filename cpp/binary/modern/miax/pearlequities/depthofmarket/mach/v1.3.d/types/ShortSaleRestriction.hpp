#pragma once

#include <cstddef>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {


// Current state of short sale restriction.
struct ShortSaleRestriction {

    static constexpr auto name = "Short Sale Restriction";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ShortSaleRestriction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ShortSaleRestriction(const char &value)
     : value{ value } {}

    // get value of ShortSaleRestriction field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
