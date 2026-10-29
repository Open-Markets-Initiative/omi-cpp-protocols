#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// QuoteCondition values
enum class QuoteCondition : char {
    RegularTrading = '1',                 // Regular Trading
    Rotation = '2',                       // Rotation
    TradingHalted = '3',                  // Trading Halted
    PreOpen = '4',                        // Pre Open
    RotationLegalWidthQuotePending = '5', // Rotation Legal Width Quote Pending
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(QuoteCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, QuoteCondition value);

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
