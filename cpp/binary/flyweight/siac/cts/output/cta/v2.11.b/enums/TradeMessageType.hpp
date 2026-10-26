#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Identifies the type of Trade message
enum class TradeMessageType : char {
    AuctionStatus = 'A',              // Auction Status
    TradeCorrection = 'C',            // Trade Correction
    FractionalTradeCorrection = 'O',  // Fractional Trade Correction
    LongTrade = 'L',                  // Long Trade
    FractionalLongTrade = 'R',        // Fractional Long Trade
    TradingStatus = 'S',              // Trading Status
    ShortTrade = 'T',                 // Short Trade
    FractionalShortTrade = 'H',       // Fractional Short Trade
    TradeCancelError = 'X',           // Trade Cancel Error
    FractionalTradeCancelError = 'E', // Fractional Trade Cancel Error
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeMessageType value);

} // namespace siac::cts::output::cta::v2_11_b
