#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_10 {

// Prior Day message type
enum class PriorDayMessageType : char {
    PriorDayTradeCorrectionMessage = 'C',            // Prior Day Trade Correction Message
    FractionalPriorDayTradeCorrectionMessage = 'O',  // Fractional Prior Day Trade Correction Message
    PriorDayTradeMessage = 'T',                      // Prior Day Trade Message
    FractionalPriorDayTradeMessage = 'R',            // Fractional Prior Day Trade Message
    PriorDayTradeCancelErrorMessage = 'X',           // Prior Day Trade Cancel Error Message
    FractionalPriorDayTradeCancelErrorMessage = 'E', // Fractional Prior Day Trade Cancel Error Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PriorDayMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PriorDayMessageType value);

} // namespace siac::cts::output::cta::v2_10
