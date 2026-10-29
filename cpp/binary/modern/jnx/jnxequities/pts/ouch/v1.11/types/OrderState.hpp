#pragma once

#include <cstddef>

namespace jnx::jnxequities::pts::ouch::v1_11 {


// Order state upon acceptance
struct OrderState {

    static constexpr auto name = "Order State";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OrderState()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderState(const char &value)
     : value{ value } {}

    // get value of OrderState field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
