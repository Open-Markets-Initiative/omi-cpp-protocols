#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Code identifying this message type
enum class MessageType : char {
    SystemEventMessage = 'S',              // System Event Message
    ComplexStrategyDirectoryMessage = 'R', // Complex Strategy Directory Message
    StrategyOpenClosedMessage = 'O',       // Strategy Open Closed Message
    StrategyTradingActionMessage = 'H',    // Strategy Trading Action Message
    StrategyBestBidAndAskUpdate = 'C',     // Strategy Best Bid And Ask Update
    StrategyBestBidUpdate = 'D',           // Strategy Best Bid Update
    StrategyBestAskUpdate = 'E',           // Strategy Best Ask Update
    ComplexStrategyTickerMessage = 't',    // Complex Strategy Ticker Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
