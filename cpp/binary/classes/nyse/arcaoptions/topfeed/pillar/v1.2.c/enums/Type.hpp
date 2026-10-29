#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Order Type of CUBE/Bold/COA
enum class Type : char {
    PriceImprovement = 'P', // Price Improvement
    Facilitation = 'F',     // Facilitation
    Solicitation = 'S',     // Solicitation
    Bold = 'B',             // Bold
    Coa = 'C',              // Coa
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Type value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Type value);

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
