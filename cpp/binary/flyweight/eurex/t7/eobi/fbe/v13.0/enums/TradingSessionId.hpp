#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v13_0 {

enum class TradingSessionId : std::uint8_t {
    Day = 1,        // Day
    Morning = 3,    // Morning
    Evening = 5,    // Evening
    AfterHours = 6, // After Hours
    Holiday = 7,    // Holiday
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingSessionId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingSessionId value);

} // namespace eurex::t7::eobi::fbe::v13_0
