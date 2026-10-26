#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// securityTradingEvent
enum class SecurityTradingEvent : std::uint8_t {
    TradingSessionChange = 4,                 // Trading Session Change
    SecurityStatusChange = 101,               // Security Status Change
    SecurityRejoinsSecurityGroupStatus = 102, // Security Rejoins Security Group Status
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityTradingEvent value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityTradingEvent value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
