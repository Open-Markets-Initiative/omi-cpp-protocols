#pragma once

#include <cstddef>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// Halt condition for option series.
struct OptionsStatusHaltCondition {

    static constexpr auto name = "Options Status Halt Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OptionsStatusHaltCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OptionsStatusHaltCondition(const char &value)
     : value{ value } {}

    // get value of OptionsStatusHaltCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
