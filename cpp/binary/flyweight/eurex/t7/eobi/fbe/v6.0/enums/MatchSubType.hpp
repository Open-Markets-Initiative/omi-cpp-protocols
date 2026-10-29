#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v6_0 {

enum class MatchSubType : std::uint8_t {
    OpeningAuction = 1,        // Opening Auction
    ClosingAuction = 2,        // Closing Auction
    IntradayAuction = 3,       // Intraday Auction
    CircuitBreakerAuction = 4, // Circuit Breaker Auction
    IpoAuction = 5,            // Ipo Auction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MatchSubType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MatchSubType value);

} // namespace eurex::t7::eobi::fbe::v6_0
