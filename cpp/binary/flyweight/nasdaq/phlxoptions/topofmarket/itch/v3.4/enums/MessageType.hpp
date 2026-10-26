#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// Code identifying this message type
enum class MessageType : char {
    TimestampMessage = 'T',                // Timestamp Message
    SystemEventMessage = 'S',              // System Event Message
    OptionsDirectoryMessage = 'D',         // Options Directory Message
    TradingActionMessage = 'H',            // Trading Action Message
    SecurityOpenClosedMessage = 'O',       // Security Open Closed Message
    ShortBestBidAndAskUpdateMessage = 'q', // Short Best Bid And Ask Update Message
    LongBestBidAndAskUpdateMessage = 'Q',  // Long Best Bid And Ask Update Message
    ShortBestAskUpdateMessage = 'a',       // Short Best Ask Update Message
    ShortBestBidUpdateMessage = 'b',       // Short Best Bid Update Message
    LongBestAskUpdateMessage = 'A',        // Long Best Ask Update Message
    LongBestBidUpdateMessage = 'B',        // Long Best Bid Update Message
    TradeReportMessage = 'R',              // Trade Report Message
    BrokenTradeReportMessage = 'X',        // Broken Trade Report Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
