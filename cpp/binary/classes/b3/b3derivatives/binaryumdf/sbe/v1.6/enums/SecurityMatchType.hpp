#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// securityMatchType
enum class SecurityMatchType : std::uint8_t {
    IssuingBuyBackAuction = 8, // Issuing Buy Back Auction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityMatchType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityMatchType value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
