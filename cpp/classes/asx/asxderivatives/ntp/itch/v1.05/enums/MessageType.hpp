#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Code identifying this message type
enum class MessageType : char {
    SecondsMessage = 'T',                        // Seconds Message
    EndOfBusinessTradeDateMessage = 'S',         // End Of Business Trade Date Message
    FutureSymbolDirectoryMessage = 'f',          // Future Symbol Directory Message
    OptionsSymbolDirectoryMessage = 'h',         // Options Symbol Directory Message
    CombinationSymbolDirectoryMessage = 'M',     // Combination Symbol Directory Message
    BundlesSymbolDirectory = 'm',                // Bundles Symbol Directory
    OrderBookStateMessage = 'O',                 // Order Book State Message
    AddOrderMessage = 'A',                       // Add Order Message
    OrderVolumeCancelledMessage = 'X',           // Order Volume Cancelled Message
    OrderDeletedMessage = 'D',                   // Order Deleted Message
    OrderExecutedMessage = 'E',                  // Order Executed Message
    AuctionOrderExecutedMessage = 'C',           // Auction Order Executed Message
    CombinationOrderExecutedMessage = 'e',       // Combination Order Executed Message
    ImpliedOrderAddedMessage = 'j',              // Implied Order Added Message
    ImpliedOrderReplacedMessage = 'l',           // Implied Order Replaced Message
    ImpliedOrderDeletedMessage = 'k',            // Implied Order Deleted Message
    TradeExecutedMessage = 'P',                  // Trade Executed Message
    CombinationTradeExecutedMessage = 'p',       // Combination Trade Executed Message
    TradeCancellationMessage = 'B',              // Trade Cancellation Message
    EquilibriumPriceMessage = 'Z',               // Equilibrium Price Message
    OpenHighLowLastTradeAdjustmentMessage = 't', // Open High Low Last Trade Adjustment Message
    MarketSettlementMessage = 'Y',               // Market Settlement Message
    TextMessage = 'x',                           // Text Message
    RequestForQuoteMessage = 'q',                // Request For Quote Message
    AnomalousOrderThresholdPublishMessage = 'W', // Anomalous Order Threshold Publish Message
    VolumeAndOpenInterestMessage = 'V',          // Volume And Open Interest Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace asx::asxderivatives::ntp::itch::v1_05
