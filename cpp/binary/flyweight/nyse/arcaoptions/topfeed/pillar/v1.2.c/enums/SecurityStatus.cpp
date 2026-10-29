#include "SecurityStatus.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

std::string_view to_string(SecurityStatus value) {
    switch (value) {
        case SecurityStatus::TradingHalt: return "Trading Halt";
        case SecurityStatus::Resume: return "Resume";
        case SecurityStatus::Suspend: return "Suspend";
        case SecurityStatus::ShortSaleRestrictionActivatedDay1: return "Short Sale Restriction Activated Day 1";
        case SecurityStatus::ShortSaleRestrictionContinuedDay2: return "Short Sale Restriction Continued Day 2";
        case SecurityStatus::ShortSaleRestrictionDeactivated: return "Short Sale Restriction Deactivated";
        case SecurityStatus::PreOpening: return "Pre Opening";
        case SecurityStatus::BeginAcceptingOrders: return "Begin Accepting Orders";
        case SecurityStatus::EarlySession: return "Early Session";
        case SecurityStatus::CoreSession: return "Core Session";
        case SecurityStatus::LateSession: return "Late Session";
        case SecurityStatus::Closed: return "Closed";
        case SecurityStatus::HaltResumePriceIndication: return "Halt Resume Price Indication";
        case SecurityStatus::PreOpeningPriceIndication: return "Pre Opening Price Indication";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
