#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// Reflects the current trading state for the issue.
enum class CurrentTradingState : char {
    HaltedPaused = 'H',  // Halted Paused
    QuotationOnly = 'Q', // Quotation Only
    Paused = 'P',        // Paused
    Trading = 'T',       // Trading
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CurrentTradingState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CurrentTradingState value);

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
