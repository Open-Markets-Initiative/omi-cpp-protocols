#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Options opening will be triggered on receipt of Opening quote/trade from this Underlying
// market
enum class OpeningUnderlyingMarketCode : char {
    NyseAmex = 'A',                        // Nyse Amex
    NasdaqOmxBx = 'B',                     // Nasdaq Omx Bx
    NationalStockExchange = 'C',           // National Stock Exchange
    FinraAdf = 'D',                        // Finra Adf
    MarketIndependent = 'E',               // Market Independent
    MiaxPearlEquities = 'H',               // Miax Pearl Equities
    InternationalSecuritiesExchange = 'I', // International Securities Exchange
    EdgaExchangeInc = 'J',                 // Edga Exchange Inc
    EdgxExchangeInc = 'K',                 // Edgx Exchange Inc
    Ltse = 'L',                            // Ltse
    ChicagoStockExchange = 'M',            // Chicago Stock Exchange
    NyseEuronext = 'N',                    // Nyse Euronext
    NyseArcaExchange = 'P',                // Nyse Arca Exchange
    NasdaqOmxUtp = 'Q',                    // Nasdaq Omx Utp
    NasdaqOmxCta = 'T',                    // Nasdaq Omx Cta
    Memx = 'U',                            // Memx
    Iex = 'V',                             // Iex
    CboeStockExchange = 'W',               // Cboe Stock Exchange
    NasdaqOmxPhlx = 'X',                   // Nasdaq Omx Phlx
    BatsY = 'Y',                           // Bats Y
    Bats = 'Z',                            // Bats
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OpeningUnderlyingMarketCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OpeningUnderlyingMarketCode value);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
