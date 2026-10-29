#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_10 {

// Identifies the instrument type relevant to the trade
enum class InstrumentType : char {
    CtaEligibleEquity = '0', // Cta Eligible Equity
    LocalIssue = '1',        // Local Issue
    CorporateBond = '2',     // Corporate Bond
    GovernmentBond = '3',    // Government Bond
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(InstrumentType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, InstrumentType value);

} // namespace siac::cts::output::cta::v2_10
