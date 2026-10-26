#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v15_0 {

enum class SecurityTradingEvent : std::uint8_t {
    PriceVolatilityAuctionIsExtended = 10,      // Price Volatility Auction Is Extended
    PriceVolatilityAuctionIsExtendedAgain = 11, // Price Volatility Auction Is Extended Again
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityTradingEvent value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityTradingEvent value);

} // namespace eurex::t7::eobi::fbe::v15_0
