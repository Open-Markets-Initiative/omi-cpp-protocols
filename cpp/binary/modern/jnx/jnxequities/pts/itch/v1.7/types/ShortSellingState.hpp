#pragma once

#include <cstddef>

namespace jnx::jnxequities::pts::itch::v1_7 {


// Current short selling price restriction state; values: 0 = No price restriction, 1 = Price restriction in effect.
struct ShortSellingState {

    static constexpr auto name = "Short Selling State";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ShortSellingState()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ShortSellingState(const char &value)
     : value{ value } {}

    // get value of ShortSellingState field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
