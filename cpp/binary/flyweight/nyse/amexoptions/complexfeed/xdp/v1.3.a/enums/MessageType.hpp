#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// The type of this message
enum class MessageType : std::uint16_t {
    ComplexQuoteMessage = 423,            // Complex Quote Message
    ComplexTradeMessage = 425,            // Complex Trade Message
    ComplexCrossingRfqMessage = 429,      // Complex Crossing Rfq Message
    ComplexCubeRfqMessage = 472,          // Complex Cube Rfq Message
    ComplexStatusMessage = 433,           // Complex Status Message
    RefreshComplexQuoteMessage = 511,     // Refresh Complex Quote Message
    RefreshComplexTradeMessage = 513,     // Refresh Complex Trade Message
    ComplexSymbolDefinitionMessage = 439, // Complex Symbol Definition Message
    StreamIdMessage = 455,                // Stream Id Message
    SequenceNumberResetMessage = 1,       // Sequence Number Reset Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
