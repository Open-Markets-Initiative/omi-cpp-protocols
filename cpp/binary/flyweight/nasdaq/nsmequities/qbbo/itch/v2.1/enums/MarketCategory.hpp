#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// Indicates Listing market or listing market tier for the issue
enum class MarketCategory : char {
    NasdaqGlobalSelectMarket = 'Q', // Nasdaq Global Select Market
    NasdaqGlobalMarket = 'G',       // Nasdaq Global Market
    NasdaqCapitalMarket = 'S',      // Nasdaq Capital Market
    NewYorkStockExchange = 'N',     // New York Stock Exchange
    NyseAmerican = 'A',             // Nyse American
    NyseArca = 'P',                 // Nyse Arca
    NyseTexas = 'M',                // Nyse Texas
    BatsBzxExchange = 'Z',          // Bats Bzx Exchange
    InvestorsExchangeLlc = 'V',     // Investors Exchange Llc
    NotAvailable = ' ',             // Not Available
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketCategory value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketCategory value);

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
