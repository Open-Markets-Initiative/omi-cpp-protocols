#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v13_0 {

enum class PotentialSecurityTradingEvent : std::uint8_t {
    None = 0,                              // None
    PriceVolatilityAuctionIsExtended = 10, // Price Volatility Auction Is Extended
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PotentialSecurityTradingEvent value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PotentialSecurityTradingEvent value);

} // namespace eurex::t7::eobi::fbe::v13_0
