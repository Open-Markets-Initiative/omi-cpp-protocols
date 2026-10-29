#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Miscellaneous state information.
enum class TradingSessionId : std::uint8_t {
    Day = 1,     // Day
    Morning = 3, // Morning
    Evening = 5, // Evening
    Holiday = 7, // Holiday
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingSessionId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingSessionId value);

} // namespace bse::bseindia::eobi::fbe::v1_4
