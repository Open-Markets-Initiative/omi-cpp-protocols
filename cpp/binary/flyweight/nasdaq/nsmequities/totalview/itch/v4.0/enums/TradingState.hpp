#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// Indicates the current trading state for the stock.
enum class TradingState : char {
    HaltedOrPaused = 'H',              // Halted Or Paused
    HaltedOrPausedOnNasdaq = 'V',      // Halted Or Paused On Nasdaq
    QuotationOnlyPeriod = 'Q',         // Quotation Only Period
    QuotationOnlyPeriodOnNasdaq = 'R', // Quotation Only Period On Nasdaq
    Trading = 'T',                     // Trading
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingState value);

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
