#pragma once

#include <cstddef>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {


// Same value as the Trade Condition sent to OPRA for this trade. To obtain a list of Trade Conditions, refer to the NOTES below.
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
