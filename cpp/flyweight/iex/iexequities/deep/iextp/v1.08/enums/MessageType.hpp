#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::deep::iextp::v1_08 {

// Code identifying this message type
enum class MessageType : char {
    SystemEventMessage = 'S',              // System Event Message
    SecurityDirectoryMessage = 'D',        // Security Directory Message
    TradingStatusMessage = 'H',            // Trading Status Message
    RetailLiquidityIndicatorMessage = 'I', // Retail Liquidity Indicator Message
    OperationalHaltStatusMessage = 'O',    // Operational Halt Status Message
    ShortSalePriceTestStatusMessage = 'P', // Short Sale Price Test Status Message
    SecurityEventMessage = 'E',            // Security Event Message
    PriceLevelBuyUpdateMessage = '8',      // Price Level Buy Update Message
    PriceLevelSellUpdateMessage = '5',     // Price Level Sell Update Message
    TradeReportMessage = 'T',              // Trade Report Message
    OfficialPriceMessage = 'X',            // Official Price Message
    TradeBreakMessage = 'B',               // Trade Break Message
    AuctionInformationMessage = 'A',       // Auction Information Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace iex::iexequities::deep::iextp::v1_08
