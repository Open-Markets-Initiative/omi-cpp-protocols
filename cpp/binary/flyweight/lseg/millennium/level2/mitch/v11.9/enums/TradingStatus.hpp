#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::millennium::level2::mitch::v11_9 {

// Trading Status
enum class TradingStatus : char {
    Active = ' ',                              // Active
    Halt = 'H',                                // Halt
    RegularTradingStartOfTradeReporting = 'T', // Regular Trading Start Of Trade Reporting
    OpeningFirstAuctionCall = 'a',             // Opening First Auction Call
    PostClose = 'b',                           // Post Close
    MarketCloseSystemShutdown = 'c',           // Market Close System Shutdown
    ClosingAuctionCall = 'd',                  // Closing Auction Call
    AespAuctionCall = 'e',                     // Aesp Auction Call
    ResumeAuctionCall = 'f',                   // Resume Auction Call
    Pause = 'l',                               // Pause
    PreMandatory = 'm',                        // Pre Mandatory
    Mandatory = 'n',                           // Mandatory
    PostMandatory = 'o',                       // Post Mandatory
    EdspAuctionCall = 'q',                     // Edsp Auction Call
    PeriodicAuctionCall = 'r',                 // Periodic Auction Call
    EndTradeReporting = 't',                   // End Trade Reporting
    NoActiveSession = 'w',                     // No Active Session
    EndOfPostClose = 'x',                      // End Of Post Close
    ClosingPriceCrossing = 'u',                // Closing Price Crossing
    ScheduledLevel1OnlyAuction = 'G',          // Scheduled Level 1 Only Auction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingStatus value);

} // namespace lseg::millennium::level2::mitch::v11_9
