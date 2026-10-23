#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// Indicates the directional relationship between the ETP and underlying index.
enum class InverseIndicator : char {
    InverseEtp = 'Y',    // Inverse Etp
    NotInverseEtp = 'N', // Not Inverse Etp
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(InverseIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, InverseIndicator value);

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
