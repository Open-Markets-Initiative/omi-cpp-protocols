#include "SecurityMassTradingEvent.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(SecurityMassTradingEvent value) {
    switch (value) {
        case SecurityMassTradingEvent::PriceVolatilityAuctionIsExtended: return "Price Volatility Auction Is Extended";
        case SecurityMassTradingEvent::PriceVolatilityAuctionIsExtendedAgain: return "Price Volatility Auction Is Extended Again";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityMassTradingEvent value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
