#pragma once

#include <cstddef>

namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29 {


// Customer Indicator
struct CustomerIndicator {

    static constexpr auto name = "Customer Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr CustomerIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CustomerIndicator(const char &value)
     : value{ value } {}

    // get value of CustomerIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
