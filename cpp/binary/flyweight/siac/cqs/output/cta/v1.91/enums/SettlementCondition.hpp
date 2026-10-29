#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v1_91 {

// Identifies the settlement condition for a security
enum class SettlementCondition : char {
    RegularWaySettlement = ' ',  // Regular Way Settlement
    CashOnlySettlement = 'A',    // Cash Only Settlement
    NextDayOnlySettlement = 'B', // Next Day Only Settlement
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SettlementCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SettlementCondition value);

} // namespace siac::cqs::output::cta::v1_91
