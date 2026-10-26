#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// protocol packet type
enum class PacketType : std::uint8_t {
    Heartbeat = 0,          // Heartbeat
    StartOfSession = 1,     // Start Of Session
    EndOfSession = 2,       // End Of Session
    ApplicationMessage = 3, // Application Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PacketType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PacketType value);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
