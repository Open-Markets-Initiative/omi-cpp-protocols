#pragma once

#include <cstddef>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {


// Options Only (byte not sent in Equities). See Options Trade Condition Codes on page 180 section for details about new codes.
struct TradeCondition {

    static constexpr auto name = "Trade Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TradeCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeCondition(const char &value)
     : value{ value } {}

    // get value of TradeCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
