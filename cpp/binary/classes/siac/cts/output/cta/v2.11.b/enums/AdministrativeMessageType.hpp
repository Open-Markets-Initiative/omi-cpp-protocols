#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Identifies the type of Administrative message
enum class AdministrativeMessageType : char {
    StartOfEndOfDaySummary = 'A',   // Start Of End Of Day Summary
    EndOfEndOfDaySummary = 'B',     // End Of End Of Day Summary
    StartOfStartOfDaySummary = 'C', // Start Of Start Of Day Summary
    EndOfStartOfDaySummary = 'D',   // End Of Start Of Day Summary
    SymbolReferenceData = 'S',      // Symbol Reference Data
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AdministrativeMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AdministrativeMessageType value);

} // namespace siac::cts::output::cta::v2_11_b
