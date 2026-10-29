#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// Code identifying this message type
enum class MessageType : char {
    SystemEventMessage = 'S',                // System Event Message
    ComplexStrategyDirectoryMessage = 'R',   // Complex Strategy Directory Message
    StrategyTradingActionMessage = 'H',      // Strategy Trading Action Message
    StrategyOpenClosedMessage = 'O',         // Strategy Open Closed Message
    ComplexStrategyOrderOnBookMessage = 'L', // Complex Strategy Order On Book Message
    ComplexStrategyAuctionMessage = 'J',     // Complex Strategy Auction Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
