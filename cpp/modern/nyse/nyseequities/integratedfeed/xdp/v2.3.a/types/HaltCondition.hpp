#pragma once

#include <cstddef>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {


// Halt condition indicator
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
