#pragma once

#include <cstddef>

namespace nyse::amexequities::integratedfeed::pillar::v2_5_g {


// The halt or other condition associated with the security status change.
struct HaltCondition {

    static constexpr auto name = "Halt Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr HaltCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit HaltCondition(const char &value)
     : value{ value } {}

    // get value of HaltCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
