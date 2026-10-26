#pragma once

#include <cstddef>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


// Bid Condition Values
struct BidCondition {

    static constexpr auto name = "Bid Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr BidCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidCondition(const char &value)
     : value{ value } {}

    // get value of BidCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
