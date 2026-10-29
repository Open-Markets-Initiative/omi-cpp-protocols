#pragma once

#include <cstddef>

namespace jnx::jnxequities::pts::ouch::v1_11 {


// Order handling instruction
struct Display {

    static constexpr auto name = "Display";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Display()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Display(const char &value)
     : value{ value } {}

    // get value of Display field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
