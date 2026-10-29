#pragma once

#include <cstddef>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {


// BZX/EDGX Options Only (space filled on C2 Options and all equities markets). N = Non-Customer C = Customer
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
