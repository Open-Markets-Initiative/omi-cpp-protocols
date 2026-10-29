#include "SecurityTradingStatus.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

std::string_view to_string(SecurityTradingStatus value) {
    switch (value) {
        case SecurityTradingStatus::TradingHalt: return "Trading Halt";
        case SecurityTradingStatus::NoOpen: return "No Open";
        case SecurityTradingStatus::ReadyToTrade: return "Ready To Trade";
        case SecurityTradingStatus::Forbidden: return "Forbidden";
        case SecurityTradingStatus::UnknownOrInvalid: return "Unknown Or Invalid";
        case SecurityTradingStatus::PreOpen: return "Pre Open";
        case SecurityTradingStatus::FinalClosingCall: return "Final Closing Call";
        case SecurityTradingStatus::Reserved: return "Reserved";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityTradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
