#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// Denotes the IPO release qualifier
enum class IpoQuotationReleaseQualifier : char {
    AnticipatedQuotationReleaseTime = 'A', // Anticipated Quotation Release Time
    IpoReleaseCanceledPostponed = 'C',     // Ipo Release Canceled Postponed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(IpoQuotationReleaseQualifier value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, IpoQuotationReleaseQualifier value);

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
