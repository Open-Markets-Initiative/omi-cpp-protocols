#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Identifies the Participant with whom a Trade Reporting Facility (TRF) has been formed.
// Space-filled
enum class TradeReportingFacilityId : char {
    TrfNotApplicable = ' ',       // Trf Not Applicable
    NotCurrentlyActiveA = 'A',    // Not Currently Active A
    FinraNasdaqTrfChicago = 'B',  // Finra Nasdaq Trf Chicago
    NotCurrentlyActiveC = 'C',    // Not Currently Active C
    NotCurrentlyActiveD = 'D',    // Not Currently Active D
    NotCurrentlyActiveI = 'I',    // Not Currently Active I
    NotCurrentlyActiveJ = 'J',    // Not Currently Active J
    NotCurrentlyActiveK = 'K',    // Not Currently Active K
    NotCurrentlyActiveM = 'M',    // Not Currently Active M
    FinraNyseTrf = 'N',           // Finra Nyse Trf
    NotCurrentlyActiveP = 'P',    // Not Currently Active P
    FinraNasdaqTrfCarteret = 'T', // Finra Nasdaq Trf Carteret
    NotCurrentlyActiveV = 'V',    // Not Currently Active V
    NotCurrentlyActiveW = 'W',    // Not Currently Active W
    NotCurrentlyActiveX = 'X',    // Not Currently Active X
    NotCurrentlyActiveY = 'Y',    // Not Currently Active Y
    NotCurrentlyActiveZ = 'Z',    // Not Currently Active Z
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeReportingFacilityId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeReportingFacilityId value);

} // namespace siac::cts::output::cta::v2_11_b
