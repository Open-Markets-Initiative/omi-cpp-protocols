#include "OperationalHaltAction.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(OperationalHaltAction value) {
    switch (value) {
        case OperationalHaltAction::Halted: return "Halted";
        case OperationalHaltAction::TradingResumed: return "Trading Resumed";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OperationalHaltAction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
