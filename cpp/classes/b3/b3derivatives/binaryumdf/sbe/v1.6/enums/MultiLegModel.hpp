#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// multiLegModel
enum class MultiLegModel : std::uint8_t {
    Predefined = 0,  // Predefined
    UserDefined = 1, // User Defined
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MultiLegModel value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MultiLegModel value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
