#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Code identifying this message type
enum class MessageType : std::uint8_t {
    SimpleInstrumentDefinitionMessage = 1,          // Simple Instrument Definition Message
    ComplexInstrumentDefinitionMessage = 2,         // Complex Instrument Definition Message
    SystemStateMessage = 3,                         // System State Message
    InstrumentTradingStatusNotificationMessage = 4, // Instrument Trading Status Notification Message
    BestBidAndOfferMessage = 15,                    // Best Bid And Offer Message
    LastSaleMessage = 16,                           // Last Sale Message
    TradeCancelMessage = 14,                        // Trade Cancel Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
