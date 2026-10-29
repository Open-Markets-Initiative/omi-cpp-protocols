#pragma once

#include <cstddef>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {


// Trade Condition Type
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
