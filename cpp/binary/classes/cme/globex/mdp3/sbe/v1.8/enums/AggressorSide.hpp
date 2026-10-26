#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_8 {

// Indicates aggressor side in the trade, if value is 0 then there is no aggressor
enum class AggressorSide : std::uint8_t {
    NoAggressor = 0, // No Aggressor
    Buy = 1,         // Buy
    Sell = 2,        // Sell
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AggressorSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AggressorSide value);

} // namespace cme::globex::mdp3::sbe::v1_8
