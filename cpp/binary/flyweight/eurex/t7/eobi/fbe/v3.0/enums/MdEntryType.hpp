#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v3_0 {

enum class MdEntryType : std::uint8_t {
    Trade = 2,                   // Trade
    OpeningPrice = 4,            // Opening Price
    ClosingPrice = 5,            // Closing Price
    HighPrice = 7,               // High Price
    LowPrice = 8,                // Low Price
    TradeVolume = 66,            // Trade Volume
    PreviousClosingPrice = 101,  // Previous Closing Price
    OpeningAuction = 200,        // Opening Auction
    IntradayAuction = 201,       // Intraday Auction
    CircuitBreakerAuction = 202, // Circuit Breaker Auction
    ClosingAuction = 203,        // Closing Auction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MdEntryType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MdEntryType value);

} // namespace eurex::t7::eobi::fbe::v3_0
