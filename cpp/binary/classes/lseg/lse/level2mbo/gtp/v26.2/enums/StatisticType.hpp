#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// The statistic that is disseminated with this message instance.
enum class StatisticType : std::uint16_t {
    IndicativeAuctionUncrossingData = 1, // Indicative Auction Uncrossing Data
    OfficialOpeningPrice = 2,            // Official Opening Price
    OfficialClosingPrice = 3,            // Official Closing Price
    TradeHighOnBook = 4,                 // Trade High On Book
    TradeLowOnBook = 5,                  // Trade Low On Book
    TradeHighAllTrades = 6,              // Trade High All Trades
    TradeLowAllTrades = 7,               // Trade Low All Trades
    FiftyTwoWeekTradeHighAllTrades = 8,  // Fifty Two Week Trade High All Trades
    FiftyTwoWeekTradeLowAllTrades = 9,   // Fifty Two Week Trade Low All Trades
    BestClosingBid = 10,                 // Best Closing Bid
    BestClosingAsk = 11,                 // Best Closing Ask
    StaticReferencePrice = 16,           // Static Reference Price
    DynamicReferencePrice = 17,          // Dynamic Reference Price
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(StatisticType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, StatisticType value);

} // namespace lseg::lse::level2mbo::gtp::v26_2
