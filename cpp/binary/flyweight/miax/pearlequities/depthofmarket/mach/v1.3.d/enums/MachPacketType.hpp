#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Mach packet type
enum class MachPacketType : std::uint8_t {
    Heartbeat = 0,          // Heartbeat
    StartOfSession = 1,     // Start Of Session
    EndOfSession = 2,       // End Of Session
    ApplicationMessage = 3, // Application Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MachPacketType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MachPacketType value);

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
