// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: enums/MsgType.cpp
#include "MsgType.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

std::string_view to_string(MsgType value) {
    switch (value) {
        case MsgType::Heartbeat: return "Heartbeat";
        case MsgType::SymbolStatusMessage: return "Symbol Status Message";
        case MsgType::OrderBookMessage: return "Order Book Message";
        case MsgType::OrderBookTermsMessage: return "Order Book Terms Message";
        case MsgType::AssignCopOrdersMessage: return "Assign Cop Orders Message";
        case MsgType::AssignCopNoOrdersMessage: return "Assign Cop No Orders Message";
        case MsgType::AssignLimitMessage: return "Assign Limit Message";
        case MsgType::MarketStateUpdateMessage: return "Market State Update Message";
        case MsgType::MocImbalanceMessage: return "Moc Imbalance Message";
        case MsgType::OrderBookedMessage: return "Order Booked Message";
        case MsgType::OrderBookedTermsMessage: return "Order Booked Terms Message";
        case MsgType::OrderCancelledMessage: return "Order Cancelled Message";
        case MsgType::OrderCancelledTermsMessage: return "Order Cancelled Terms Message";
        case MsgType::OrderPriceTimeAssignedMessage: return "Order Price Time Assigned Message";
        case MsgType::OrderPriceTimeAssignedTermsMessage: return "Order Price Time Assigned Terms Message";
        case MsgType::StockStatusMessage: return "Stock Status Message";
        case MsgType::TradeReportMessage: return "Trade Report Message";
        case MsgType::TradeReportTermsMessage: return "Trade Report Terms Message";
        case MsgType::TradeCancelledMessage: return "Trade Cancelled Message";
        case MsgType::TradeCancelledTermsMessage: return "Trade Cancelled Terms Message";
        case MsgType::TradeCorrectionMessage: return "Trade Correction Message";
        case MsgType::TradeCorrectionTermsMessage: return "Trade Correction Terms Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MsgType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
