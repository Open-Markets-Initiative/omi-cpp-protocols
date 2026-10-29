#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Type of the trade.
enum class TradeType : std::uint8_t {
    RegularOrContinuousTrade = 0, // Regular Or Continuous Trade
    AuctionTradeBulk = 1,         // Auction Trade Bulk
    AuctionTradeIndividual = 2,   // Auction Trade Individual
    OnBookTradeCancellation = 9,  // On Book Trade Cancellation
    TradeCorrection = 11,         // Trade Correction
    RfqTrade = 22,                // Rfq Trade
    RfqTradeCancellation = 23,    // Rfq Trade Cancellation
    RfqTradeCorrection = 24,      // Rfq Trade Correction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeType value);

} // namespace lseg::lse::level2mbo::gtp::v26_2
