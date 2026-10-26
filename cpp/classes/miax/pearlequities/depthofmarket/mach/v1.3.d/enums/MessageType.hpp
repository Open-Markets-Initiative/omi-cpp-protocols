#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Code identifying this message type
enum class MessageType : std::uint8_t {
    SystemTimeMessage = 49,                       // System Time Message
    SymbolUpdateMessage = 1,                      // Symbol Update Message
    SystemStateMessage = 83,                      // System State Message
    SecurityTradingStatusNotificationMessage = 4, // Security Trading Status Notification Message
    SymbolClearMessage = 5,                       // Symbol Clear Message
    AddOrderMessage = 20,                         // Add Order Message
    ModifyOrderMessage = 21,                      // Modify Order Message
    DeleteOrderMessage = 23,                      // Delete Order Message
    OrderExecutionMessage = 24,                   // Order Execution Message
    TradeMessage = 10,                            // Trade Message
    TradeCancelMessage = 11,                      // Trade Cancel Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
