#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::tops::iextp::v1_56 {

// Code identifying this message type
enum class MessageType : char {
    QuoteUpdateMessage = 'Q', // Quote Update Message
    TradeReportMessage = 'T', // Trade Report Message
    TradeBreakMessage = 'B',  // Trade Break Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace iex::iexequities::tops::iextp::v1_56
