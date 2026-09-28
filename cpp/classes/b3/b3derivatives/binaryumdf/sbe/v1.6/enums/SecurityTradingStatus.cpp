#include "SecurityTradingStatus.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

std::string_view to_string(SecurityTradingStatus value) {
    switch (value) {
        case SecurityTradingStatus::Pause: return "Pause";
        case SecurityTradingStatus::Close: return "Close";
        case SecurityTradingStatus::Open: return "Open";
        case SecurityTradingStatus::Forbidden: return "Forbidden";
        case SecurityTradingStatus::UnknownOrInvalid: return "Unknown Or Invalid";
        case SecurityTradingStatus::Reserved: return "Reserved";
        case SecurityTradingStatus::FinalClosingCall: return "Final Closing Call";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityTradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
