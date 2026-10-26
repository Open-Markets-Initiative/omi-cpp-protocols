#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::opra::output::obi::v6_2 {

// Identifies the participant that entered the Best Bid.
enum class BestOfferParticipantId : char {
    NyseAmerican = 'A',                         // Nyse American
    BostonOptionsExchange = 'B',                // Boston Options Exchange
    CboeOptionsExchange = 'C',                  // Cboe Options Exchange
    MiaxEmerald = 'D',                          // Miax Emerald
    CboeEdgxOptions = 'E',                      // Cboe Edgx Options
    NasdaqGemx = 'H',                           // Nasdaq Gemx
    NasdaqIse = 'I',                            // Nasdaq Ise
    NasdaqMrx = 'J',                            // Nasdaq Mrx
    MiamiInternationalSecuritiesExchange = 'M', // Miami International Securities Exchange
    NyseArca = 'N',                             // Nyse Arca
    OptionsPriceReportingAuthority = 'O',       // Options Price Reporting Authority
    MiaxPearl = 'P',                            // Miax Pearl
    NasdaqOptionsMarket = 'Q',                  // Nasdaq Options Market
    NasdaqBxOptions = 'T',                      // Nasdaq Bx Options
    CboeC2Options = 'W',                        // Cboe C 2 Options
    NasdaqPhlx = 'X',                           // Nasdaq Phlx
    CboeBzxOptionsExchange = 'Z',               // Cboe Bzx Options Exchange
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(BestOfferParticipantId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, BestOfferParticipantId value);

} // namespace siac::opra::output::obi::v6_2
