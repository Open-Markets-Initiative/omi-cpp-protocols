#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// posMaintStatus
enum class PosMaintStatus : char {
    Accepted = '0',    // Accepted
    Rejected = '2',    // Rejected
    Completed = '3',   // Completed
    NotExecuted = '9', // Not Executed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PosMaintStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PosMaintStatus value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
