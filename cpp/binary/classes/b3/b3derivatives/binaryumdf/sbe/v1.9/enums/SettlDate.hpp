// B3.B3Derivatives.BinaryUmdf.Sbe.v1.9: enums/SettlDate.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// settlDate
enum class SettlDate : std::int32_t {
    NoEndDate = 2932896, // No End Date
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SettlDate value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SettlDate value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
