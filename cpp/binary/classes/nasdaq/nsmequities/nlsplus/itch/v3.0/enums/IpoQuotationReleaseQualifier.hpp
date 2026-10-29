#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Denotes whether the release time is anticipated or the release has been cancelled or
// postponed
enum class IpoQuotationReleaseQualifier : char {
    Anticipated = 'A', // Anticipated
    Cancelled = 'C',   // Cancelled
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(IpoQuotationReleaseQualifier value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, IpoQuotationReleaseQualifier value);

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
