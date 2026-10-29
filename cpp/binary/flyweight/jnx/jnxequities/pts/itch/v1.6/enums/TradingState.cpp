#include "TradingState.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

std::string_view to_string(TradingState value) {
    switch (value) {
        case TradingState::Trading: return "Trading";
        case TradingState::Suspended: return "Suspended";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::itch::v1_6
