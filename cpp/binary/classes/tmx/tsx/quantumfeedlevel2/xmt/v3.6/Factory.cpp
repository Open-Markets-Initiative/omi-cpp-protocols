// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: Factory.cpp
#include "Factory.hpp"

#include "definitions.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SymbolStatusMessage::message_type: return std::make_unique<SymbolStatusMessage>();
        case OrderBookMessage::message_type: return std::make_unique<OrderBookMessage>();
        case OrderBookTermsMessage::message_type: return std::make_unique<OrderBookTermsMessage>();
        case AssignCopOrdersMessage::message_type: return std::make_unique<AssignCopOrdersMessage>();
        case AssignCopNoOrdersMessage::message_type: return std::make_unique<AssignCopNoOrdersMessage>();
        case AssignLimitMessage::message_type: return std::make_unique<AssignLimitMessage>();
        case MarketStateUpdateMessage::message_type: return std::make_unique<MarketStateUpdateMessage>();
        case MocImbalanceMessage::message_type: return std::make_unique<MocImbalanceMessage>();
        case OrderBookedMessage::message_type: return std::make_unique<OrderBookedMessage>();
        case OrderBookedTermsMessage::message_type: return std::make_unique<OrderBookedTermsMessage>();
        case OrderCancelledMessage::message_type: return std::make_unique<OrderCancelledMessage>();
        case OrderCancelledTermsMessage::message_type: return std::make_unique<OrderCancelledTermsMessage>();
        case OrderPriceTimeAssignedMessage::message_type: return std::make_unique<OrderPriceTimeAssignedMessage>();
        case OrderPriceTimeAssignedTermsMessage::message_type: return std::make_unique<OrderPriceTimeAssignedTermsMessage>();
        case StockStatusMessage::message_type: return std::make_unique<StockStatusMessage>();
        case TradeReportMessage::message_type: return std::make_unique<TradeReportMessage>();
        case TradeReportTermsMessage::message_type: return std::make_unique<TradeReportTermsMessage>();
        case TradeCancelledMessage::message_type: return std::make_unique<TradeCancelledMessage>();
        case TradeCancelledTermsMessage::message_type: return std::make_unique<TradeCancelledTermsMessage>();
        case TradeCorrectionMessage::message_type: return std::make_unique<TradeCorrectionMessage>();
        case TradeCorrectionTermsMessage::message_type: return std::make_unique<TradeCorrectionTermsMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
