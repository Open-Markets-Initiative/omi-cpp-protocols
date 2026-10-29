#include "SecurityTradingEvent.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

std::string_view to_string(SecurityTradingEvent value) {
    switch (value) {
        case SecurityTradingEvent::PriceVolatilityAuctionIsExtended: return "Price Volatility Auction Is Extended";
        case SecurityTradingEvent::PriceVolatilityAuctionIsExtendedAgain: return "Price Volatility Auction Is Extended Again";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityTradingEvent value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v6_0
