#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Order Type of CUBE/BOLD/COA
enum class Type : char {
    BoldOutrightOnly = 'B',         // Bold Outright Only
    CoaComplexOnly = 'C',           // Coa Complex Only
    FlexPriceImprovementCube = 'F', // Flex Price Improvement Cube
    FlexAonSolicitationCube = 'L',  // Flex Aon Solicitation Cube
    PriceImprovementCube = 'P',     // Price Improvement Cube
    AonSolicitationCube = 'S',      // Aon Solicitation Cube
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Type value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Type value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
