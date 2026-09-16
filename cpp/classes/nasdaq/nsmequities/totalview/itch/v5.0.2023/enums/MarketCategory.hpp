#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Indicates listing market or listing market tier for the issue
enum class MarketCategory : char {
    NasdaqGlobalSelectMarket = 'Q', // Nasdaq Global Select Market
    NasdaqGlobalMarket = 'G',       // Nasdaq Global Market
    NasdaqCapitalMarket = 'S',      // Nasdaq Capital Market
    Nyse = 'N',                     // Nyse
    NyseAmerican = 'A',             // Nyse American
    NyseArca = 'P',                 // Nyse Arca
    NyseTexas = 'M',                // Nyse Texas
    BatsZ = 'Z',                    // Bats Z
    InvestorsExchange = 'V',        // Investors Exchange
    NotAvailable = ' ',             // Not Available
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketCategory value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketCategory value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
