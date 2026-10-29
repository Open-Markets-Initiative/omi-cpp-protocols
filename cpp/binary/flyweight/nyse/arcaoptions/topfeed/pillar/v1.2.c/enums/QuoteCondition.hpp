#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Quote Condition
enum class QuoteCondition : char {
    RegularTrading = '1', // Regular Trading
    Rotation = '2',       // Rotation
    TradingHalted = '3',  // Trading Halted
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(QuoteCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, QuoteCondition value);

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
