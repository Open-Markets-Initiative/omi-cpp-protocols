#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Current trading status of the instrument.
enum class TradingStatus : char {
    Halt = 'H',                              // Halt
    HaltMatchingPartitionSuspended = 'J',    // Halt Matching Partition Suspended
    HaltSystemSuspended = 'K',               // Halt System Suspended
    RegularTradingStartTradeReporting = 'T', // Regular Trading Start Trade Reporting
    HaltRegulatory = 'P',                    // Halt Regulatory
    EndTradeReporting = 't',                 // End Trade Reporting
    OpeningAuctionCall = 'a',                // Opening Auction Call
    PostClose = 'b',                         // Post Close
    Closed = 'c',                            // Closed
    ClosingAuctionCall = 'd',                // Closing Auction Call
    AespAuctionCall = 'e',                   // Aesp Auction Call
    ResumeAuction = 'f',                     // Resume Auction
    PreMandatory = 'm',                      // Pre Mandatory
    Mandatory = 'n',                         // Mandatory
    PostMandatory = 'o',                     // Post Mandatory
    EdspAuctionCall = 'q',                   // Edsp Auction Call
    PeriodicAuctionCall = 'r',               // Periodic Auction Call
    Inactive = '1',                          // Inactive
    Suspended = '2',                         // Suspended
    NoActiveSession = 'w',                   // No Active Session
    EndOfPostClose = 'x',                    // End Of Post Close
    ClosingPriceCrossingSession = 'u',       // Closing Price Crossing Session
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingStatus value);

} // namespace lseg::lse::level2mbo::gtp::v26_2
