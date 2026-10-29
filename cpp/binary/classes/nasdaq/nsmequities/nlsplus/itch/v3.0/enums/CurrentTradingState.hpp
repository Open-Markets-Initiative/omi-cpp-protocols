#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Reflects the current trading state for the issue
enum class CurrentTradingState : char {
    Halted = 'H',        // Halted
    Paused = 'P',        // Paused
    QuotationOnly = 'Q', // Quotation Only
    Trading = 'T',       // Trading
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CurrentTradingState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CurrentTradingState value);

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
