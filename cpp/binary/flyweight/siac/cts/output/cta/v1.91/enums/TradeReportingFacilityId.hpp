#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v1_91 {

// Identifies the Participant with whom a Trade Reporting Facility has been formed
enum class TradeReportingFacilityId : char {
    NotApplicable = ' ',       // Not Applicable
    InactiveValueA = 'A',      // Inactive Value A
    FinraNasdaqChicago = 'B',  // Finra Nasdaq Chicago
    InactiveValueC = 'C',      // Inactive Value C
    InactiveValueD = 'D',      // Inactive Value D
    InactiveValueI = 'I',      // Inactive Value I
    InactiveValueJ = 'J',      // Inactive Value J
    InactiveValueK = 'K',      // Inactive Value K
    InactiveValueM = 'M',      // Inactive Value M
    FinraNyse = 'N',           // Finra Nyse
    InactiveValueP = 'P',      // Inactive Value P
    FinraNasdaqCarteret = 'T', // Finra Nasdaq Carteret
    InactiveValueV = 'V',      // Inactive Value V
    InactiveValueW = 'W',      // Inactive Value W
    InactiveValueX = 'X',      // Inactive Value X
    InactiveValueY = 'Y',      // Inactive Value Y
    InactiveValueZ = 'Z',      // Inactive Value Z
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeReportingFacilityId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeReportingFacilityId value);

} // namespace siac::cts::output::cta::v1_91
