#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Identifies series type
enum class SeriesType : std::uint8_t {
    Standard = 0,       // Standard
    Flex = 1,           // Flex
    FlexPercentage = 2, // Flex Percentage
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SeriesType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SeriesType value);

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
