#include "SecurityStatus.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(SecurityStatus value) {
    switch (value) {
        case SecurityStatus::SecurityStatusNotApplicable: return "Security Status Not Applicable";
        case SecurityStatus::Reserved1: return "Reserved 1";
        case SecurityStatus::TradingHalt: return "Trading Halt";
        case SecurityStatus::Resume: return "Resume";
        case SecurityStatus::Reserved4: return "Reserved 4";
        case SecurityStatus::PriceIndication: return "Price Indication";
        case SecurityStatus::TradingRangeIndication: return "Trading Range Indication";
        case SecurityStatus::MarketImbalanceBuy: return "Market Imbalance Buy";
        case SecurityStatus::MarketImbalanceSell: return "Market Imbalance Sell";
        case SecurityStatus::ClosingImbalanceBuy: return "Closing Imbalance Buy";
        case SecurityStatus::ClosingImbalanceSell: return "Closing Imbalance Sell";
        case SecurityStatus::ReservedB: return "Reserved B";
        case SecurityStatus::NoMarketImbalance: return "No Market Imbalance";
        case SecurityStatus::NoClosingImbalance: return "No Closing Imbalance";
        case SecurityStatus::ShortSaleRestriction: return "Short Sale Restriction";
        case SecurityStatus::LimitUpLimitDown: return "Limit Up Limit Down";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
