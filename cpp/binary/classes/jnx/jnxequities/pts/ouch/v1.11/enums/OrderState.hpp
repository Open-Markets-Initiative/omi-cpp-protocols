#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Order state upon acceptance
enum class OrderState : char {
    Live = 'L', // Live
    Dead = 'D', // Dead
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OrderState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OrderState value);

} // namespace jnx::jnxequities::pts::ouch::v1_11
