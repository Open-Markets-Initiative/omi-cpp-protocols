// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: enums/GoodbyeReason.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// GoodBye Packet Reason
enum class GoodbyeReason : char {
    BadPacket = 'B',                        // Bad Packet
    TimedOut = 'L',                         // Timed Out
    ApplicationTerminatingConnection = 'A', // Application Terminating Connection
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(GoodbyeReason value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, GoodbyeReason value);

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
