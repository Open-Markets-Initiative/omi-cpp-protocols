#pragma once

#include <cstddef>

namespace jnx::jnxequities::pts::ouch::v1_11 {


// Capacity of firm placing order
struct Capacity {

    static constexpr auto name = "Capacity";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Capacity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Capacity(const char &value)
     : value{ value } {}

    // get value of Capacity field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
