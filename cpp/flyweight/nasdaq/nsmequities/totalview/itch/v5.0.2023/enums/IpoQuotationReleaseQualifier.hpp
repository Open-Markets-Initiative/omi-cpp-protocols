#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// IPO Quotation Release Qualifier
enum class IpoQuotationReleaseQualifier : char {
    AnticipatedQuotationReleaseTime = 'A', // Anticipated Quotation Release Time
    IpoReleaseCanceledOrPostponed = 'C',   // Ipo Release Canceled Or Postponed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(IpoQuotationReleaseQualifier value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, IpoQuotationReleaseQualifier value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
