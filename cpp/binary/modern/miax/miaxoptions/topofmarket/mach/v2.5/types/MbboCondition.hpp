#pragma once

#include <cstddef>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


// MBBO Condition Values
struct MbboCondition {

    static constexpr auto name = "Mbbo Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MbboCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MbboCondition(const char &value)
     : value{ value } {}

    // get value of MbboCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
