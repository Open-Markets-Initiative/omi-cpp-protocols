#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Product state information.
enum class TradingSessionSubId : std::uint8_t {
    PreTrading = 1,  // Pre Trading
    Trading = 3,     // Trading
    Closing = 4,     // Closing
    PostTrading = 5, // Post Trading
    PostClosing = 6, // Post Closing
    Quiescent = 7,   // Quiescent
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingSessionSubId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingSessionSubId value);

} // namespace bse::bseindia::eobi::fbe::v1_4
