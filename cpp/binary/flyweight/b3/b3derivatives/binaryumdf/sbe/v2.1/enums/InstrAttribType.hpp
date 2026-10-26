#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// Code to represent the type of instrument attributes.
enum class InstrAttribType : std::uint8_t {
    TradeTypeEligibility = 24, // Trade Type Eligibility
    GtdGtcEligibility = 34,    // Gtd Gtc Eligibility
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(InstrAttribType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, InstrAttribType value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
