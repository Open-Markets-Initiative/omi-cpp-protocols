#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_13 {

// Aggressor Indicator 1=Aggressor Order 0=Passive Order
enum class AggressorIndicator : std::uint8_t {
    NotAggressor = 0, // Not Aggressor
    Aggressor = 1,    // Aggressor
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AggressorIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AggressorIndicator value);

} // namespace cme::globex::mdp3::sbe::v1_13
