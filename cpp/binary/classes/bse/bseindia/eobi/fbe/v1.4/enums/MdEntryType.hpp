#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Type of market data entry.
enum class MdEntryType : std::uint8_t {
    Trade = 2,                   // Trade
    OpeningPrice = 4,            // Opening Price
    ClosingPrice = 5,            // Closing Price
    HighPrice = 7,               // High Price
    LowPrice = 8,                // Low Price
    PreviousClosingPrice = 101,  // Previous Closing Price
    OpeningAuction = 200,        // Opening Auction
    IntradayAuction = 201,       // Intraday Auction
    CircuitBreakerAuction = 202, // Circuit Breaker Auction
    ClosingAuction = 203,        // Closing Auction
    UpperCktLimit = 204,         // Upper Ckt Limit
    LowerCktLimit = 205,         // Lower Ckt Limit
    GrossTradeAmt = 206,         // Gross Trade Amt
    UpperExecLimit = 208,        // Upper Exec Limit
    LowerExecLimit = 209,        // Lower Exec Limit
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MdEntryType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MdEntryType value);

} // namespace bse::bseindia::eobi::fbe::v1_4
