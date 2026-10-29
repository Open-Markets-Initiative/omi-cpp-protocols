#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// crossType
enum class CrossType : std::uint8_t {
    AllOrNoneCross = 1,                     // All Or None Cross
    CrossExecutedAgainstBookFromClient = 4, // Cross Executed Against Book From Client
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CrossType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CrossType value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
