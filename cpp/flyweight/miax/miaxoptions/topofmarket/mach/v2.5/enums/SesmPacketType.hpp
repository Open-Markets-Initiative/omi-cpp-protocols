#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// SesM protocol packet type
enum class SesmPacketType : char {
    SequencedDataPacket = 's',     // Sequenced Data Packet
    UnsequencedDataPacket = 'U',   // Unsequenced Data Packet
    LoginRequest = 'l',            // Login Request
    LoginResponse = 'r',           // Login Response
    SynchronizationComplete = 'c', // Synchronization Complete
    RetransmissionRequest = 'a',   // Retransmission Request
    LogoutRequest = 'X',           // Logout Request
    GoodbyePacket = 'G',           // Goodbye Packet
    TradingSessionUpdate = 'u',    // Trading Session Update
    ServerHeartbeat = '0',         // Server Heartbeat
    ClientHeartbeat = '1',         // Client Heartbeat
    TestPacket = 'T',              // Test Packet
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SesmPacketType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SesmPacketType value);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
