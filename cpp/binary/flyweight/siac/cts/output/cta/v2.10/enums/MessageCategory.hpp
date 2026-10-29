#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_10 {

// The Message Category represents the message classification
enum class MessageCategory : char {
    Administrative = 'A', // Administrative
    Control = 'C',        // Control
    Indices = 'I',        // Indices
    MarketStatus = 'M',   // Market Status
    PriorDay = 'P',       // Prior Day
    Summary = 'S',        // Summary
    Trade = 'T',          // Trade
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageCategory value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageCategory value);

} // namespace siac::cts::output::cta::v2_10
