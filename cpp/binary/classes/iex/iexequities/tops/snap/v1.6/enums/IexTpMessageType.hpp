#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::tops::snap::v1_6 {

// Code identifying the wrapped Tops message type
enum class IexTpMessageType : char {
    SystemEventMessage = 'S',              // System Event Message
    SecurityDirectoryMessage = 'D',        // Security Directory Message
    TradingStatusMessage = 'H',            // Trading Status Message
    RetailLiquidityIndicatorMessage = 'I', // Retail Liquidity Indicator Message
    OperationalHaltStatusMessage = 'O',    // Operational Halt Status Message
    ShortSalePriceTestStatusMessage = 'P', // Short Sale Price Test Status Message
    QuoteUpdateMessage = 'Q',              // Quote Update Message
    TradeReportMessage = 'T',              // Trade Report Message
    OfficialPriceMessage = 'X',            // Official Price Message
    TradeBreakMessage = 'B',               // Trade Break Message
    AuctionInformationMessage = 'A',       // Auction Information Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(IexTpMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, IexTpMessageType value);

} // namespace iex::iexequities::tops::snap::v1_6
