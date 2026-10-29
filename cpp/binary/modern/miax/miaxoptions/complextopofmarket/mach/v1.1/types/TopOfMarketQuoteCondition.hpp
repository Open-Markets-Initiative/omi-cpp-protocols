#pragma once

#include <cstddef>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {


// Top of Strategy Market Quote Conditions
struct TopOfMarketQuoteCondition {

    static constexpr auto name = "Top Of Market Quote Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TopOfMarketQuoteCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TopOfMarketQuoteCondition(const char &value)
     : value{ value } {}

    // get value of TopOfMarketQuoteCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
