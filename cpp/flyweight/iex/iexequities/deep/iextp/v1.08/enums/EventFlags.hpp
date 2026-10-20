#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::deep::iextp::v1_08 {

// Identifies event processing by the System
enum class EventFlags : std::uint8_t {
    OrderBookIsProcessingAnEvent = 0, // Order Book Is Processing An Event
    EventProcessingComplete = 1,      // Event Processing Complete
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(EventFlags value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, EventFlags value);

} // namespace iex::iexequities::deep::iextp::v1_08
