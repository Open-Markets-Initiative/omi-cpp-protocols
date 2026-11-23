// B3.B3Derivatives.BinaryUmdf.Sbe.v2.3: enums/SettlDateLocalMktDate32Optional.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// settlDate
enum class SettlDateLocalMktDate32Optional : std::int32_t {
    NoEndDate = 2932896, // No End Date
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SettlDateLocalMktDate32Optional value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SettlDateLocalMktDate32Optional value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
