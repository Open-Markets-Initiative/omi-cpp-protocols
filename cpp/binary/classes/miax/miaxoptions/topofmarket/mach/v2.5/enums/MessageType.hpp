#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Code identifying this message type
enum class MessageType : char {
    SystemTimeMessage = '1',                                        // System Time Message
    SimpleSeriesUpdateMessage = 'P',                                // Simple Series Update Message
    SystemStateMessage = 'S',                                       // System State Message
    SimpleTopOfMarketBestBidOrOfferCompactBidMessage = 'B',         // Simple Top Of Market Best Bid Or Offer Compact Bid Message
    SimpleTopOfMarketBestBidOrOfferCompactOfferMessage = 'O',       // Simple Top Of Market Best Bid Or Offer Compact Offer Message
    SimpleTopOfMarketBestBidOrOfferWideBidMessage = 'b',            // Simple Top Of Market Best Bid Or Offer Wide Bid Message
    SimpleTopOfMarketBestBidOrOfferWideOfferMessage = 'o',          // Simple Top Of Market Best Bid Or Offer Wide Offer Message
    SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage = 'd', // Simple Double Sided Top Of Market Best Bid Or Offer Compact Message
    SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage = 'D',    // Simple Double Sided Top Of Market Best Bid Or Offer Wide Message
    LastSaleMessage = 'T',                                          // Last Sale Message
    TradeCancelMessage = 'X',                                       // Trade Cancel Message
    UnderlyingTradingStatusNotificationMessage = 'H',               // Underlying Trading Status Notification Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
