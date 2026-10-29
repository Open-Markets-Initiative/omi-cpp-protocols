#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// posTransType
enum class PosTransType : std::uint8_t {
    Exercise = 1,               // Exercise
    AutomaticExercise = 105,    // Automatic Exercise
    ExerciseNotAutomatic = 106, // Exercise Not Automatic
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PosTransType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PosTransType value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
