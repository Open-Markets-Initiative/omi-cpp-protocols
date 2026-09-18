#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// First byte of the tag identifying the message type used as dispatch key
enum class MessageType : char {
    SecondsTimestampMessage = 'T',       // Seconds Timestamp Message
    TradingStatusMessage = 'O',          // Trading Status Message
    ExecutionSummaryMessage = 'K',       // Execution Summary Message
    AddOrderMessage = 'A',               // Add Order Message
    OrderExecutedMessage = 'E',          // Order Executed Message
    OrderExecutedWithPriceMessage = 'C', // Order Executed With Price Message
    OrderDeleteMessage = 'D',            // Order Delete Message
    ResetMessage = 'R',                  // Reset Message
    CommunicationControlMessage = 'L',   // Communication Control Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
