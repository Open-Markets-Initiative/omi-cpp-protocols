#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// exerciseStyle
enum class ExerciseStyle : std::uint8_t {
    European = 0, // European
    American = 1, // American
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ExerciseStyle value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ExerciseStyle value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
