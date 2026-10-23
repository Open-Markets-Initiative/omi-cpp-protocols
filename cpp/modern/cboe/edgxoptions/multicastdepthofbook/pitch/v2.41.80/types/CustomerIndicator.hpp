#pragma once

#include <cstddef>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {


// BZX/C1/EDGX Options Only (space filled on C2 Options and all equities markets). N = Non-Customer, C = Customer, R = Retail Priority order (EDGX Equities only).
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
