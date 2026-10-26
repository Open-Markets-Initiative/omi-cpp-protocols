#include "RefreshMessageType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

std::string_view to_string(RefreshMessageType value) {
    switch (value) {
        case RefreshMessageType::SymbolUpdateRefresh: return "Symbol Update Refresh";
        case RefreshMessageType::SecurityTradingStatusRefresh: return "Security Trading Status Refresh";
        case RefreshMessageType::SystemStateRefresh: return "System State Refresh";
        case RefreshMessageType::OrderBookRefresh: return "Order Book Refresh";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RefreshMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
