#include "SecurityTradingStatus.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

std::string_view to_string(SecurityTradingStatus value) {
    switch (value) {
        case SecurityTradingStatus::TradingHalt: return "Trading Halt";
        case SecurityTradingStatus::Close: return "Close";
        case SecurityTradingStatus::NewPriceIndication: return "New Price Indication";
        case SecurityTradingStatus::ReadyToTrade: return "Ready To Trade";
        case SecurityTradingStatus::NotAvailableForTrading: return "Not Available For Trading";
        case SecurityTradingStatus::UnknownorInvalid: return "Unknownor Invalid";
        case SecurityTradingStatus::PreOpen: return "Pre Open";
        case SecurityTradingStatus::PreCross: return "Pre Cross";
        case SecurityTradingStatus::Cross: return "Cross";
        case SecurityTradingStatus::PostClose: return "Post Close";
        case SecurityTradingStatus::NoChange: return "No Change";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityTradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_8
