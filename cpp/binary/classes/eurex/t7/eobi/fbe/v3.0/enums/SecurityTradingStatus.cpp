#include "SecurityTradingStatus.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

std::string_view to_string(SecurityTradingStatus value) {
    switch (value) {
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
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityTradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v3_0
