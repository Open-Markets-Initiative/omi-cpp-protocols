#include "SecurityStatus.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

std::string_view to_string(SecurityStatus value) {
    switch (value) {
        case SecurityStatus::OpeningDelay: return "Opening Delay";
        case SecurityStatus::TradingHalt: return "Trading Halt";
        case SecurityStatus::Resume: return "Resume";
        case SecurityStatus::NoOpennoResume: return "No Openno Resume";
        case SecurityStatus::ShortSaleRestrictionActivatedDay1: return "Short Sale Restriction Activated Day 1";
        case SecurityStatus::ShortSaleRestrictionContinuedDay2: return "Short Sale Restriction Continued Day 2";
        case SecurityStatus::ShortSaleRestrictionDeactivated: return "Short Sale Restriction Deactivated";
        case SecurityStatus::PreOpening: return "Pre Opening";
        case SecurityStatus::EarlySession: return "Early Session";
        case SecurityStatus::CoreSession: return "Core Session";
        case SecurityStatus::LateSessionNonNyseOnly: return "Late Session Non Nyse Only";
        case SecurityStatus::Closed: return "Closed";
        case SecurityStatus::Time: return "Time";
        case SecurityStatus::PriceIndication: return "Price Indication";
        case SecurityStatus::PreOpeningPriceIndication: return "Pre Opening Price Indication";
        case SecurityStatus::Rule15Indication: return "Rule 15 Indication";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nyseequities::bbo::xdp::v2_4_g
