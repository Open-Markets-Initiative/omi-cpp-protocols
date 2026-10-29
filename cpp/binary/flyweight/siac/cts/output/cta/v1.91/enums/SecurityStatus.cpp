#include "SecurityStatus.hpp"

namespace siac::cts::output::cta::v1_91 {

std::string_view to_string(SecurityStatus value) {
    switch (value) {
        case SecurityStatus::NotApplicable: return "Not Applicable";
        case SecurityStatus::OpeningDelay: return "Opening Delay";
        case SecurityStatus::TradingHalt: return "Trading Halt";
        case SecurityStatus::Resume: return "Resume";
        case SecurityStatus::NoOpenNoResume: return "No Open No Resume";
        case SecurityStatus::PriceIndication: return "Price Indication";
        case SecurityStatus::TradingRangeIndication: return "Trading Range Indication";
        case SecurityStatus::MarketImbalanceBuy: return "Market Imbalance Buy";
        case SecurityStatus::MarketImbalanceSell: return "Market Imbalance Sell";
        case SecurityStatus::MarketOnCloseImbalanceBuy: return "Market On Close Imbalance Buy";
        case SecurityStatus::MarketOnCloseImbalanceSell: return "Market On Close Imbalance Sell";
        case SecurityStatus::Reserved: return "Reserved";
        case SecurityStatus::NoMarketImbalance: return "No Market Imbalance";
        case SecurityStatus::NoMarketOnCloseImbalance: return "No Market On Close Imbalance";
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

} // namespace siac::cts::output::cta::v1_91
