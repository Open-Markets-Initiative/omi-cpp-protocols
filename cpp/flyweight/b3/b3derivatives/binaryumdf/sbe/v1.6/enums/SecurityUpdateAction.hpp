#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// securityUpdateAction
enum class SecurityUpdateAction : char {
    Add = 'A',    // Add
    Delete = 'D', // Delete
    Modify = 'M', // Modify
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityUpdateAction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityUpdateAction value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
