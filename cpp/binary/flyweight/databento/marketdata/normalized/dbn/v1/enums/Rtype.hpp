#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v1 {

// The record type, which selects the record that follows the header
enum class Rtype : std::uint8_t {
    MarketByPrice0 = 0,               // Market By Price 0
    MarketByPrice1 = 1,               // Market By Price 1
    MarketByPrice10 = 10,             // Market By Price 10
    OhlcvDeprecated = 17,             // Ohlcv Deprecated
    Status = 18,                      // Status
    InstrumentDefinition = 19,        // Instrument Definition
    Imbalance = 20,                   // Imbalance
    Error = 21,                       // Error
    SymbolMapping = 22,               // Symbol Mapping
    System = 23,                      // System
    Statistics = 24,                  // Statistics
    Ohlcv1Second = 32,                // Ohlcv 1 Second
    Ohlcv1Minute = 33,                // Ohlcv 1 Minute
    Ohlcv1Hour = 34,                  // Ohlcv 1 Hour
    Ohlcv1Day = 35,                   // Ohlcv 1 Day
    OhlcvEndOfDay = 36,               // Ohlcv End Of Day
    MarketByOrder = 160,              // Market By Order
    ConsolidatedMarketByPrice1 = 177, // Consolidated Market By Price 1
    ConsolidatedBbo1Second = 192,     // Consolidated Bbo 1 Second
    ConsolidatedBbo1Minute = 193,     // Consolidated Bbo 1 Minute
    TradeWithConsolidatedBbo = 194,   // Trade With Consolidated Bbo
    Bbo1Second = 195,                 // Bbo 1 Second
    Bbo1Minute = 196,                 // Bbo 1 Minute
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Rtype value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Rtype value);

} // namespace databento::marketdata::normalized::dbn::v1
