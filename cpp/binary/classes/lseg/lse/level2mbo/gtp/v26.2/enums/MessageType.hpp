#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Code identifying this message type
enum class MessageType : std::uint8_t {
    SystemEventMessage = 83,          // System Event Message
    InstrumentDirectoryMessage = 112, // Instrument Directory Message
    InstrumentStatusMessage = 72,     // Instrument Status Message
    AddOrderMboMessage = 65,          // Add Order Mbo Message
    AddOrderShortMboMessage = 101,    // Add Order Short Mbo Message
    OrderBookClearMessage = 121,      // Order Book Clear Message
    TradeMessage = 80,                // Trade Message
    StatisticsMessage = 119,          // Statistics Message
    StatisticsUpdateMessage = 106,    // Statistics Update Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace lseg::lse::level2mbo::gtp::v26_2
