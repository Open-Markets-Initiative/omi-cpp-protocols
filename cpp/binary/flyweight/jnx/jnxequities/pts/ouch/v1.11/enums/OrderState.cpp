#include "OrderState.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

std::string_view to_string(OrderState value) {
    switch (value) {
        case OrderState::Live: return "Live";
        case OrderState::Dead: return "Dead";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OrderState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
