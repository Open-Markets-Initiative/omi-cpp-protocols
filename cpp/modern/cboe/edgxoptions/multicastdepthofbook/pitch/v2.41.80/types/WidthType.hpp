#pragma once

#include <cstddef>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {


// R = Regular, V = Volatility.
struct WidthType {

    static constexpr auto name = "Width Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr WidthType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit WidthType(const char &value)
     : value{ value } {}

    // get value of WidthType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
