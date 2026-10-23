#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_13 {

// Status of the request acknowledgement
enum class MdReqIdStatus : std::uint8_t {
    FullAck = 0,    // Full Ack
    PartialAck = 1, // Partial Ack
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MdReqIdStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MdReqIdStatus value);

} // namespace cme::globex::mdp3::sbe::v1_13
