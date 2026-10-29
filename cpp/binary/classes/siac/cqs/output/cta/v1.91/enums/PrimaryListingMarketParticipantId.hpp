#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v1_91 {

// Identifies the Primary Listing Market for a security
enum class PrimaryListingMarketParticipantId : char {
    PrimaryListingMarketParticipantIdNotApplicable = ' ', // Primary Listing Market Participant Id Not Applicable
    NyseAmerican = 'A',                                   // Nyse American
    NasdaqOmxBx = 'B',                                    // Nasdaq Omx Bx
    NyseNational = 'C',                                   // Nyse National
    FinraAdf = 'D',                                       // Finra Adf
    Ise = 'I',                                            // Ise
    CboeEdga = 'J',                                       // Cboe Edga
    CboeEdgx = 'K',                                       // Cboe Edgx
    NyseChicago = 'M',                                    // Nyse Chicago
    Nyse = 'N',                                           // Nyse
    NyseArca = 'P',                                       // Nyse Arca
    Nasdaq = 'T',                                         // Nasdaq
    Iex = 'V',                                            // Iex
    Cbsx = 'W',                                           // Cbsx
    NasdaqOmxPsx = 'X',                                   // Nasdaq Omx Psx
    CboeByx = 'Y',                                        // Cboe Byx
    CboeBzx = 'Z',                                        // Cboe Bzx
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PrimaryListingMarketParticipantId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PrimaryListingMarketParticipantId value);

} // namespace siac::cqs::output::cta::v1_91
