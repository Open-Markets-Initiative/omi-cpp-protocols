// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/IsConditional.hpp
#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {


// Indicates A Firm Up Conditional To Firm Up Conditional Execution
struct IsConditional {

    static constexpr auto name = "Is Conditional";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr IsConditional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IsConditional(const char &value)
     : value{ value } {}

    // get value of IsConditional field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
