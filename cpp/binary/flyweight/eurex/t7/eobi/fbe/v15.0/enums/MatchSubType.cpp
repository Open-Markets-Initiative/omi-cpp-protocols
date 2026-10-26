#include "MatchSubType.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(MatchSubType value) {
    switch (value) {
        case MatchSubType::OpeningAuction: return "Opening Auction";
        case MatchSubType::ClosingAuction: return "Closing Auction";
        case MatchSubType::IntradayAuction: return "Intraday Auction";
        case MatchSubType::CircuitBreakerAuction: return "Circuit Breaker Auction";
        case MatchSubType::IpoAuction: return "Ipo Auction";
        case MatchSubType::RetailAuctionVolaTrade: return "Retail Auction Vola Trade";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MatchSubType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
