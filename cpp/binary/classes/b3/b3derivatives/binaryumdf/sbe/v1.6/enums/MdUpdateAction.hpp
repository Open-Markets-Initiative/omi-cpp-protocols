#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// mDUpdateAction
enum class MdUpdateAction : std::uint8_t {
    New = 0,        // New
    Change = 1,     // Change
    Delete = 2,     // Delete
    DeleteThru = 3, // Delete Thru
    DeleteFrom = 4, // Delete From
    Overlay = 5,    // Overlay
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MdUpdateAction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MdUpdateAction value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
