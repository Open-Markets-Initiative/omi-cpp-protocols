// Databento.MarketData.Normalized.Dbn.v2: enums/Schema.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v2 {

// The data record schema; no value for a file of mixed schemas
enum class Schema : std::uint16_t {
    Mbo = 0,         // Mbo
    Mbp1 = 1,        // Mbp1
    Mbp10 = 2,       // Mbp10
    Tbbo = 3,        // Tbbo
    Trades = 4,      // Trades
    Ohlcv1S = 5,     // Ohlcv1 S
    Ohlcv1M = 6,     // Ohlcv1 M
    Ohlcv1H = 7,     // Ohlcv1 H
    Ohlcv1D = 8,     // Ohlcv1 D
    Definition = 9,  // Definition
    Statistics = 10, // Statistics
    Status = 11,     // Status
    Imbalance = 12,  // Imbalance
    OhlcvEod = 13,   // Ohlcv Eod
    Cmbp1 = 14,      // Cmbp1
    Cbbo1S = 15,     // Cbbo1 S
    Cbbo1M = 16,     // Cbbo1 M
    Tcbbo = 17,      // Tcbbo
    Bbo1S = 18,      // Bbo1 S
    Bbo1M = 19,      // Bbo1 M
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Schema value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Schema value);

} // namespace databento::marketdata::normalized::dbn::v2
