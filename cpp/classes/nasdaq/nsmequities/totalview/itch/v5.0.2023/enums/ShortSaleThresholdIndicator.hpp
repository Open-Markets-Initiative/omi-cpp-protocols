#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Indicates if a security is subject to mandatory close-out of short sales under SEC Rule
// 203(b)(3).
enum class ShortSaleThresholdIndicator : char {
    Restricted = 'Y',    // Restricted
    NotRestricted = 'N', // Not Restricted
    NotAvailable = ' ',  // Not Available
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ShortSaleThresholdIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ShortSaleThresholdIndicator value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
