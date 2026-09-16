#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Code identifying this message type
enum class MessageType : char {
    SystemEventMessage = 'S',                                 // System Event Message
    StockDirectoryMessage = 'R',                              // Stock Directory Message
    StockTradingActionMessage = 'H',                          // Stock Trading Action Message
    RegShoShortSalePriceTestRestrictedIndicatorMessage = 'Y', // Reg Sho Short Sale Price Test Restricted Indicator Message
    MarketParticipantPositionMessage = 'L',                   // Market Participant Position Message
    MwcbDeclineLevelMessage = 'V',                            // Mwcb Decline Level Message
    MwcbStatusLevelMessage = 'W',                             // Mwcb Status Level Message
    IpoQuotingPeriodUpdate = 'K',                             // Ipo Quoting Period Update
    LuldAuctionCollarMessage = 'J',                           // Luld Auction Collar Message
    OperationalHaltMessage = 'h',                             // Operational Halt Message
    AddOrderNoMpidAttributionMessage = 'A',                   // Add Order No Mpid Attribution Message
    AddOrderWithMpidAttributionMessage = 'F',                 // Add Order With Mpid Attribution Message
    OrderExecutedMessage = 'E',                               // Order Executed Message
    OrderExecutedWithPriceMessage = 'C',                      // Order Executed With Price Message
    OrderCancelMessage = 'X',                                 // Order Cancel Message
    OrderDeleteMessage = 'D',                                 // Order Delete Message
    OrderReplaceMessage = 'U',                                // Order Replace Message
    NonCrossTradeMessage = 'P',                               // Non Cross Trade Message
    CrossTradeMessage = 'Q',                                  // Cross Trade Message
    BrokenTradeMessage = 'B',                                 // Broken Trade Message
    NetOrderImbalanceIndicatorMessage = 'I',                  // Net Order Imbalance Indicator Message
    RetailPriceImprovementIndicatorMessage = 'N',             // Retail Price Improvement Indicator Message
    DirectListingWithCapitalRaisePriceDiscoveryMessage = 'O', // Direct Listing With Capital Raise Price Discovery Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
