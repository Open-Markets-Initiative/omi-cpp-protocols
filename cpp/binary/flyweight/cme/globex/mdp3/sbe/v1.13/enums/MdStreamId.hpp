#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_13 {

// Source of the Clean Price
enum class MdStreamId : std::uint8_t {
    MarketPlaceAssistant = 0, // Market Place Assistant
    Globex = 1,               // Globex
    Refinitiv = 2,            // Refinitiv
    Icap = 3,                 // Icap
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MdStreamId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MdStreamId value);

} // namespace cme::globex::mdp3::sbe::v1_13
