#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v15_0 {

enum class SecurityMassTradingStatus : std::uint8_t {
    TradingHalt = 2,                                               // Trading Halt
    MarketImbalanceBuy = 7,                                        // Market Imbalance Buy
    MarketImbalanceSell = 8,                                       // Market Imbalance Sell
    Closed = 200,                                                  // Closed
    Restricted = 201,                                              // Restricted
    Book = 202,                                                    // Book
    Continuous = 203,                                              // Continuous
    OpeningAuction = 204,                                          // Opening Auction
    OpeningAuctionFreeze = 205,                                    // Opening Auction Freeze
    IntradayAuction = 206,                                         // Intraday Auction
    IntradayAuctionFreeze = 207,                                   // Intraday Auction Freeze
    CircuitBreakerAuction = 208,                                   // Circuit Breaker Auction
    CircuitBreakerAuctionFreeze = 209,                             // Circuit Breaker Auction Freeze
    ClosingAuction = 210,                                          // Closing Auction
    ClosingAuctionFreeze = 211,                                    // Closing Auction Freeze
    IpoAuction = 212,                                              // Ipo Auction
    IpoAuctionFreeze = 213,                                        // Ipo Auction Freeze
    PreCall = 214,                                                 // Pre Call
    Call = 215,                                                    // Call
    Freeze = 216,                                                  // Freeze
    TradeAtClose = 217,                                            // Trade At Close
    RetailPreCall = 218,                                           // Retail Pre Call
    RetailCall = 219,                                              // Retail Call
    CircuitBreakerAuctionTriggeredByStaticLimitBreach = 220,       // Circuit Breaker Auction Triggered By Static Limit Breach
    CircuitBreakerAuctionTriggeredByStaticLimitBreachFreeze = 221, // Circuit Breaker Auction Triggered By Static Limit Breach Freeze
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityMassTradingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityMassTradingStatus value);

} // namespace eurex::t7::eobi::fbe::v15_0
