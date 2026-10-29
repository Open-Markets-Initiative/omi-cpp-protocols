#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v1_91 {

// Identifies the market condition of a quote for a security.
enum class MarketCondition : char {
    NormalAuctionMarket = ' ', // Normal Auction Market
    CrossedMarket = 'A',       // Crossed Market
    LockedMarket = 'B',        // Locked Market
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketCondition value);

} // namespace siac::cqs::output::cta::v1_91
