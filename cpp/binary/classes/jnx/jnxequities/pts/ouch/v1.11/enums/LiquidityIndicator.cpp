#include "LiquidityIndicator.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

std::string_view to_string(LiquidityIndicator value) {
    switch (value) {
        case LiquidityIndicator::Added: return "Added";
        case LiquidityIndicator::Removed: return "Removed";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LiquidityIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
