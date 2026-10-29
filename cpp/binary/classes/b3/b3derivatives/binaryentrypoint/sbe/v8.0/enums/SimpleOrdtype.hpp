#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// ordType
enum class SimpleOrdtype : char {
    Market = '1', // Market
    Limit = '2',  // Limit
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SimpleOrdtype value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SimpleOrdtype value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
