#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// securityIDSource
enum class SecurityIdSource : char {
    Isin = '4',           // Isin
    ExchangeSymbol = '8', // Exchange Symbol
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityIdSource value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityIdSource value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
