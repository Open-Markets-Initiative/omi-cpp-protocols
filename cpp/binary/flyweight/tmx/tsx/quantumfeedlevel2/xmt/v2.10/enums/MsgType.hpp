// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: enums/MsgType.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Msg Type
enum class MsgType : char {
    Heartbeat = '0',                          // Heartbeat
    SymbolStatusMessage = 'J',                // Symbol Status Message
    OrderBookMessage = 'G',                   // Order Book Message
    OrderBookTermsMessage = 'j',              // Order Book Terms Message
    AssignCopOrdersMessage = 'A',             // Assign Cop Orders Message
    AssignCopNoOrdersMessage = 'B',           // Assign Cop No Orders Message
    AssignLimitMessage = 'C',                 // Assign Limit Message
    MarketStateUpdateMessage = 'E',           // Market State Update Message
    MocImbalanceMessage = 'F',                // Moc Imbalance Message
    OrderBookedMessage = 'P',                 // Order Booked Message
    OrderBookedTermsMessage = 'm',            // Order Booked Terms Message
    OrderCancelledMessage = 'Q',              // Order Cancelled Message
    OrderCancelledTermsMessage = 'n',         // Order Cancelled Terms Message
    OrderPriceTimeAssignedMessage = 'R',      // Order Price Time Assigned Message
    OrderPriceTimeAssignedTermsMessage = 'o', // Order Price Time Assigned Terms Message
    StockStatusMessage = 'I',                 // Stock Status Message
    TradeReportMessage = 'S',                 // Trade Report Message
    TradeReportTermsMessage = 'p',            // Trade Report Terms Message
    TradeCancelledMessage = 'T',              // Trade Cancelled Message
    TradeCancelledTermsMessage = 'q',         // Trade Cancelled Terms Message
    TradeCorrectionMessage = 'U',             // Trade Correction Message
    TradeCorrectionTermsMessage = 'r',        // Trade Correction Terms Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MsgType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MsgType value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
