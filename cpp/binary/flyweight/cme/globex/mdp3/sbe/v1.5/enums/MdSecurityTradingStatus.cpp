#include "MdSecurityTradingStatus.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

std::string_view to_string(MdSecurityTradingStatus value) {
    switch (value) {
        case MdSecurityTradingStatus::TradingHalt: return "Trading Halt";
        case MdSecurityTradingStatus::Close: return "Close";
        case MdSecurityTradingStatus::NewPriceIndication: return "New Price Indication";
        case MdSecurityTradingStatus::ReadyToTrade: return "Ready To Trade";
        case MdSecurityTradingStatus::NotAvailableForTrading: return "Not Available For Trading";
        case MdSecurityTradingStatus::UnknownOrInvalid: return "Unknown Or Invalid";
        case MdSecurityTradingStatus::PreOpen: return "Pre Open";
        case MdSecurityTradingStatus::PreCross: return "Pre Cross";
        case MdSecurityTradingStatus::Cross: return "Cross";
        case MdSecurityTradingStatus::PostClose: return "Post Close";
        case MdSecurityTradingStatus::NoChange: return "No Change";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MdSecurityTradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_5
