#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Indicates if the security is eligible to be released for trading
enum class OpenEligibilityStatus : char {
    NotEligible = 'N', // Not Eligible
    Eligible = 'Y',    // Eligible
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OpenEligibilityStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OpenEligibilityStatus value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
