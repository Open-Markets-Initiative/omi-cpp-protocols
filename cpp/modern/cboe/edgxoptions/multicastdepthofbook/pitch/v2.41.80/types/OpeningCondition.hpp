#pragma once

#include <cstddef>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {


// O = Would open, Q = Need quote to open, B = Need more buyers (C1 Only), S = Need more sellers (C1 Only), C = Crossed Composite Market.
struct OpeningCondition {

    static constexpr auto name = "Opening Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OpeningCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OpeningCondition(const char &value)
     : value{ value } {}

    // get value of OpeningCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
