#include "SecurityTradingStatus.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(SecurityTradingStatus value) {
    switch (value) {
        case SecurityTradingStatus::TradingHalt: return "Trading Halt";
        case SecurityTradingStatus::MarketImbalanceBuy: return "Market Imbalance Buy";
        case SecurityTradingStatus::MarketImbalanceSell: return "Market Imbalance Sell";
        case SecurityTradingStatus::Closed: return "Closed";
        case SecurityTradingStatus::Restricted: return "Restricted";
        case SecurityTradingStatus::Book: return "Book";
        case SecurityTradingStatus::Continuous: return "Continuous";
        case SecurityTradingStatus::OpeningAuction: return "Opening Auction";
        case SecurityTradingStatus::OpeningAuctionFreeze: return "Opening Auction Freeze";
        case SecurityTradingStatus::IntradayAuction: return "Intraday Auction";
        case SecurityTradingStatus::IntradayAuctionFreeze: return "Intraday Auction Freeze";
        case SecurityTradingStatus::CircuitBreakerAuction: return "Circuit Breaker Auction";
        case SecurityTradingStatus::CircuitBreakerAuctionFreeze: return "Circuit Breaker Auction Freeze";
        case SecurityTradingStatus::ClosingAuction: return "Closing Auction";
        case SecurityTradingStatus::ClosingAuctionFreeze: return "Closing Auction Freeze";
        case SecurityTradingStatus::IpoAuction: return "Ipo Auction";
        case SecurityTradingStatus::IpoAuctionFreeze: return "Ipo Auction Freeze";
        case SecurityTradingStatus::PreCall: return "Pre Call";
        case SecurityTradingStatus::Call: return "Call";
        case SecurityTradingStatus::Freeze: return "Freeze";
        case SecurityTradingStatus::TradeAtClose: return "Trade At Close";
        case SecurityTradingStatus::RetailPreCall: return "Retail Pre Call";
        case SecurityTradingStatus::RetailCall: return "Retail Call";
        case SecurityTradingStatus::CircuitBreakerAuctionTriggeredByStaticLimitBreach: return "Circuit Breaker Auction Triggered By Static Limit Breach";
        case SecurityTradingStatus::CircuitBreakerAuctionTriggeredByStaticLimitBreachFreeze: return "Circuit Breaker Auction Triggered By Static Limit Breach Freeze";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityTradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
