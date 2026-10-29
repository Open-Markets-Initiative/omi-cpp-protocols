#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

// Indicates the current trading state for the stock.
enum class TradingState : char {
    Halted = 'H',        // Halted
    Paused = 'P',        // Paused
    QuotationOnly = 'Q', // Quotation Only
    Trading = 'T',       // Trading
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingState value);

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
