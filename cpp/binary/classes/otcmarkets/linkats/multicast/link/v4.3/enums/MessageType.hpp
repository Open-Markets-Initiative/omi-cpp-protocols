#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Code identifying this message type
enum class MessageType : std::uint8_t {
    StartOfSpinMessage = 11,             // Start Of Spin Message
    EndOfSpinMessage = 12,               // End Of Spin Message
    MarketOpenMessage = 13,              // Market Open Message
    MarketCloseMessage = 14,             // Market Close Message
    SecurityMessage = 9,                 // Security Message
    QuoteMessage = 1,                    // Quote Message
    QuoteUpdateMessage = 2,              // Quote Update Message
    InsideMessage = 3,                   // Inside Message
    InsideUpdateMessage = 4,             // Inside Update Message
    ReferencePriceMessage = 7,           // Reference Price Message
    ReferencePriceUpdateMessage = 8,     // Reference Price Update Message
    ExtendedSecurityMessage = 15,        // Extended Security Message
    ExtendedSecurityNoCusipMessage = 16, // Extended Security No Cusip Message
    TradeMessage = 17,                   // Trade Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace otcmarkets::linkats::multicast::link::v4_3
