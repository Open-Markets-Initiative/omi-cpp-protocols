#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Trading state of the order book
enum class SymbolState : char {
    Closed = 'C',                   // Closed
    PreOpen = 'P',                  // Pre Open
    OpeningAuction = 'O',           // Opening Auction
    ContinuousTrading = 'T',        // Continuous Trading
    ScheduledIntradayAuction = 'I', // Scheduled Intraday Auction
    ClosingAuction = 'L',           // Closing Auction
    PostTrade = 'S',                // Post Trade
    Halted = 'H',                   // Halted
    AuctionPeriod = 'Q',            // Auction Period
    TradingAtClosingPrice = 'A',    // Trading At Closing Price
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SymbolState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SymbolState value);

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
