#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Indicates the current trading state for the stock
enum class TradingState : char {
    Halted = 'H',              // Halted
    Paused = 'P',              // Paused
    QuotationOnlyPeriod = 'Q', // Quotation Only Period
    Trading = 'T',             // Trading
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingState value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
