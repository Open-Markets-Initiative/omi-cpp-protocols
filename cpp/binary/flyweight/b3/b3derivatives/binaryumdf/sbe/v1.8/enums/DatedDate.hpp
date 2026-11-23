// B3.B3Derivatives.BinaryUmdf.Sbe.v1.8: enums/DatedDate.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// datedDate
enum class DatedDate : std::int32_t {
    NoEndDate = 2932896, // No End Date
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(DatedDate value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, DatedDate value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
