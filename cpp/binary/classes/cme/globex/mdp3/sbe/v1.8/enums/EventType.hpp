#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_8 {

// Code to represent the type of event
enum class EventType : std::uint8_t {
    Activation = 5,            // Activation
    LastEligibleTradeDate = 7, // Last Eligible Trade Date
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(EventType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, EventType value);

} // namespace cme::globex::mdp3::sbe::v1_8
