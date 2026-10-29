#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// allocStatus
enum class AllocStatus : char {
    Accepted = '0',               // Accepted
    RejectedByIntermediary = '5', // Rejected By Intermediary
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AllocStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AllocStatus value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
