#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_10 {

// Identifies the Consolidated High/Low/Last Price applicable to the trade.
enum class ConsolidatedHighLowLastIndicator : char {
    None = 'A',        // None
    High = 'B',        // High
    Low = 'C',         // Low
    Last = 'D',        // Last
    HighLast = 'E',    // High Last
    LowLast = 'F',     // Low Last
    HighLowLast = 'G', // High Low Last
    HighLow = 'H',     // High Low
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ConsolidatedHighLowLastIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ConsolidatedHighLowLastIndicator value);

} // namespace siac::cts::output::cta::v2_10
