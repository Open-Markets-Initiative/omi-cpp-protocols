#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jnx::jnxequities::pts::itch::v1_7 {

// Type of the order.
enum class OrderType : char {
    DlpOrder = 'Q', // Dlp Order
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OrderType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OrderType value);

} // namespace jnx::jnxequities::pts::itch::v1_7
