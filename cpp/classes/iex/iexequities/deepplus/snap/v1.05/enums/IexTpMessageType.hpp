#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::deepplus::snap::v1_05 {

// Code identifying the wrapped Deep Plus message type
enum class IexTpMessageType : char {
    SystemEventMessage = 'S',              // System Event Message
    SecurityDirectoryMessage = 'D',        // Security Directory Message
    TradingStatusMessage = 'H',            // Trading Status Message
    RetailLiquidityIndicatorMessage = 'I', // Retail Liquidity Indicator Message
    OperationalHaltStatusMessage = 'O',    // Operational Halt Status Message
    ShortSalePriceTestStatusMessage = 'P', // Short Sale Price Test Status Message
    SecurityEventMessage = 'E',            // Security Event Message
    AddOrderMessage = 'a',                 // Add Order Message
    OrderModifyMessage = 'M',              // Order Modify Message
    OrderDeleteMessage = 'R',              // Order Delete Message
    OrderExecutedMessage = 'L',            // Order Executed Message
    TradeMessage = 'T',                    // Trade Message
    TradeBreakMessage = 'B',               // Trade Break Message
    ClearBookMessage = 'C',                // Clear Book Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(IexTpMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, IexTpMessageType value);

} // namespace iex::iexequities::deepplus::snap::v1_05
