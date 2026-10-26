#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Indicates the directional relationship between the ETP and underlying index. Example: An ETP
// Leverage Factor of 3 and an Inverse value of 'Y' indicates the ETP will decrease by a value
// of 3.
enum class InverseIndicator : char {
    InverseEtp = 'Y',    // Inverse Etp
    NotInverseEtp = 'N', // Not Inverse Etp
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(InverseIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, InverseIndicator value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
