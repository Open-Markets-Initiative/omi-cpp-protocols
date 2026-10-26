#include "SecurityTradingEvent.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

std::string_view to_string(SecurityTradingEvent value) {
    switch (value) {
        case SecurityTradingEvent::TradingSessionChange: return "Trading Session Change";
        case SecurityTradingEvent::SecurityStatusChange: return "Security Status Change";
        case SecurityTradingEvent::SecurityRejoinsSecurityGroupStatus: return "Security Rejoins Security Group Status";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityTradingEvent value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
