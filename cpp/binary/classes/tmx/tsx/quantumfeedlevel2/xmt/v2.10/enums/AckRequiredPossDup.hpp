// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: enums/AckRequiredPossDup.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Ack Required Poss Dup
enum class AckRequiredPossDup : char {
    Unused = '0',      // Unused
    AckRequired = 'A', // Ack Required
    PossDup = 'D',     // Poss Dup
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AckRequiredPossDup value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AckRequiredPossDup value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
