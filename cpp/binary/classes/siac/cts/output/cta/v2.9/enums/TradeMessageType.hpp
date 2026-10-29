#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_9 {

// Trade message type
enum class TradeMessageType : char {
    AuctionStatusMessage = 'A',    // Auction Status Message
    TradeCorrectionMessage = 'C',  // Trade Correction Message
    LongTradeMessage = 'L',        // Long Trade Message
    TradingStatusMessage = 'S',    // Trading Status Message
    ShortTradeMessage = 'T',       // Short Trade Message
    TradeCancelErrorMessage = 'X', // Trade Cancel Error Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeMessageType value);

} // namespace siac::cts::output::cta::v2_9
