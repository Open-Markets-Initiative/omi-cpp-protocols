#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Instrument state status.
enum class SecurityTradingStatus : std::uint8_t {
    Closed = 200,                      // Closed
    Restricted = 201,                  // Restricted
    Book = 202,                        // Book
    Continuous = 203,                  // Continuous
    OpeningAuction = 204,              // Opening Auction
    OpeningAuctionFreeze = 205,        // Opening Auction Freeze
    IntradayAuction = 206,             // Intraday Auction
    IntradayAuctionFreeze = 207,       // Intraday Auction Freeze
    CircuitBreakerAuction = 208,       // Circuit Breaker Auction
    CircuitBreakerAuctionFreeze = 209, // Circuit Breaker Auction Freeze
    ClosingAuction = 210,              // Closing Auction
    ClosingAuctionFreeze = 211,        // Closing Auction Freeze
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityTradingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityTradingStatus value);

} // namespace bse::bseindia::eobi::fbe::v1_4
