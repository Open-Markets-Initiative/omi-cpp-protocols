#pragma once

#include <cstddef>

namespace jnx::jnxequities::pts::ouch::v1_11 {


// System event code
struct SystemEvent {

    static constexpr auto name = "System Event";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SystemEvent()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SystemEvent(const char &value)
     : value{ value } {}

    // get value of SystemEvent field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
