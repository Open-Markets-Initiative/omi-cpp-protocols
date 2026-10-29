#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

// Code identifying this message type
enum class MessageType : char {
    SystemEventMessage = 'S',                                 // System Event Message
    StockDirectoryMessage = 'R',                              // Stock Directory Message
    StockTradingActionMessage = 'H',                          // Stock Trading Action Message
    RegShoShortSalePriceTestRestrictedIndicatorMessage = 'Y', // Reg Sho Short Sale Price Test Restricted Indicator Message
    MarketParticipantPositionMessage = 'L',                   // Market Participant Position Message
    MwcbDeclineLevelMessage = 'V',                            // Mwcb Decline Level Message
    MwcbStatusMessage = 'W',                                  // Mwcb Status Message
    LuldAuctionCollarMessage = 'J',                           // Luld Auction Collar Message
    OperationalHaltMessage = 'h',                             // Operational Halt Message
    AddOrderNoMpidAttributionMessage = 'A',                   // Add Order No Mpid Attribution Message
    AddOrderMpidAttributionMessage = 'F',                     // Add Order Mpid Attribution Message
    OrderExecutedMessage = 'E',                               // Order Executed Message
    OrderExecutedWithPriceMessage = 'C',                      // Order Executed With Price Message
    OrderCancelMessage = 'X',                                 // Order Cancel Message
    OrderDeleteMessage = 'D',                                 // Order Delete Message
    OrderReplaceMessage = 'U',                                // Order Replace Message
    NonCrossTradeMessage = 'P',                               // Non Cross Trade Message
    CrossTradeMessage = 'Q',                                  // Cross Trade Message
    BrokenTradeMessage = 'B',                                 // Broken Trade Message
    NetOrderImbalanceIndicatorMessage = 'I',                  // Net Order Imbalance Indicator Message
    RetailInterestMessage = 'N',                              // Retail Interest Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
