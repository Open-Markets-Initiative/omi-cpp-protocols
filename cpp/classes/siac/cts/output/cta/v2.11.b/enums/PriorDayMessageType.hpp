#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Identifies the type of Prior Day message
enum class PriorDayMessageType : char {
    PriorDayTradeCorrection = 'C',            // Prior Day Trade Correction
    FractionalPriorDayTradeCorrection = 'O',  // Fractional Prior Day Trade Correction
    PriorDayTrade = 'T',                      // Prior Day Trade
    FractionalPriorDayTrade = 'R',            // Fractional Prior Day Trade
    PriorDayTradeCancelError = 'X',           // Prior Day Trade Cancel Error
    FractionalPriorDayTradeCancelError = 'E', // Fractional Prior Day Trade Cancel Error
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PriorDayMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PriorDayMessageType value);

} // namespace siac::cts::output::cta::v2_11_b
