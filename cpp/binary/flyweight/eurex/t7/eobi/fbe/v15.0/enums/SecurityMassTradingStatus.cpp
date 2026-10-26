#include "SecurityMassTradingStatus.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(SecurityMassTradingStatus value) {
    switch (value) {
        case SecurityMassTradingStatus::TradingHalt: return "Trading Halt";
        case SecurityMassTradingStatus::MarketImbalanceBuy: return "Market Imbalance Buy";
        case SecurityMassTradingStatus::MarketImbalanceSell: return "Market Imbalance Sell";
        case SecurityMassTradingStatus::Closed: return "Closed";
        case SecurityMassTradingStatus::Restricted: return "Restricted";
        case SecurityMassTradingStatus::Book: return "Book";
        case SecurityMassTradingStatus::Continuous: return "Continuous";
        case SecurityMassTradingStatus::OpeningAuction: return "Opening Auction";
        case SecurityMassTradingStatus::OpeningAuctionFreeze: return "Opening Auction Freeze";
        case SecurityMassTradingStatus::IntradayAuction: return "Intraday Auction";
        case SecurityMassTradingStatus::IntradayAuctionFreeze: return "Intraday Auction Freeze";
        case SecurityMassTradingStatus::CircuitBreakerAuction: return "Circuit Breaker Auction";
        case SecurityMassTradingStatus::CircuitBreakerAuctionFreeze: return "Circuit Breaker Auction Freeze";
        case SecurityMassTradingStatus::ClosingAuction: return "Closing Auction";
        case SecurityMassTradingStatus::ClosingAuctionFreeze: return "Closing Auction Freeze";
        case SecurityMassTradingStatus::IpoAuction: return "Ipo Auction";
        case SecurityMassTradingStatus::IpoAuctionFreeze: return "Ipo Auction Freeze";
        case SecurityMassTradingStatus::PreCall: return "Pre Call";
        case SecurityMassTradingStatus::Call: return "Call";
        case SecurityMassTradingStatus::Freeze: return "Freeze";
        case SecurityMassTradingStatus::TradeAtClose: return "Trade At Close";
        case SecurityMassTradingStatus::RetailPreCall: return "Retail Pre Call";
        case SecurityMassTradingStatus::RetailCall: return "Retail Call";
        case SecurityMassTradingStatus::CircuitBreakerAuctionTriggeredByStaticLimitBreach: return "Circuit Breaker Auction Triggered By Static Limit Breach";
        case SecurityMassTradingStatus::CircuitBreakerAuctionTriggeredByStaticLimitBreachFreeze: return "Circuit Breaker Auction Triggered By Static Limit Breach Freeze";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityMassTradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
