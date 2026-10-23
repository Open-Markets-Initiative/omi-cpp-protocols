#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Identifies the Primary Listing Market of the security symbol
enum class PrimaryListingMarketParticipantId : char {
    PrimaryListingMarketParticipantIdNotApplicable = ' ', // Primary Listing Market Participant Id Not Applicable
    NyseAmerican = 'A',                                   // Nyse American
    NasdaqBx = 'B',                                       // Nasdaq Bx
    NyseNational = 'C',                                   // Nyse National
    FinraAdf = 'D',                                       // Finra Adf
    TexasStockExchange = 'F',                             // Texas Stock Exchange
    N24x = 'G',                                           // N24X
    MiaxPearl = 'H',                                      // Miax Pearl
    Ise = 'I',                                            // Ise
    CboeEdga = 'J',                                       // Cboe Edga
    CboeEdgx = 'K',                                       // Cboe Edgx
    Ltse = 'L',                                           // Ltse
    NyseTexas = 'M',                                      // Nyse Texas
    Nyse = 'N',                                           // Nyse
    NyseArca = 'P',                                       // Nyse Arca
    Nasdaq = 'T',                                         // Nasdaq
    MembersExchange = 'U',                                // Members Exchange
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

} // namespace siac::cts::output::cta::v2_11_b
