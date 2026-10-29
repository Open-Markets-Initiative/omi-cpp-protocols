#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_9 {

// Identifies the Participant with whom a Trade Reporting Facility has been formed
enum class TradeReportingFacilityId : char {
    NotApplicable = ' ',       // Not Applicable
    FinraNasdaqChicago = 'B',  // Finra Nasdaq Chicago
    FinraNyse = 'N',           // Finra Nyse
    FinraNasdaqCarteret = 'T', // Finra Nasdaq Carteret
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeReportingFacilityId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeReportingFacilityId value);

} // namespace siac::cts::output::cta::v2_9
