#include "Factory.hpp"

#include "definitions.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SecondsTimestampMessage::message_type: return std::make_unique<SecondsTimestampMessage>();
        case TradingStatusMessage::message_type: return std::make_unique<TradingStatusMessage>();
        case ExecutionSummaryMessage::message_type: return std::make_unique<ExecutionSummaryMessage>();
        case AddOrderMessage::message_type: return std::make_unique<AddOrderMessage>();
        case OrderExecutedMessage::message_type: return std::make_unique<OrderExecutedMessage>();
        case OrderExecutedWithPriceMessage::message_type: return std::make_unique<OrderExecutedWithPriceMessage>();
        case OrderDeleteMessage::message_type: return std::make_unique<OrderDeleteMessage>();
        case ResetMessage::message_type: return std::make_unique<ResetMessage>();
        case CommunicationControlMessage::message_type: return std::make_unique<CommunicationControlMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

std::unique_ptr<TcpMessage> TcpMessageFactory::create(TcpMessageCode code) {
    switch (code) {
        case LoginRequestMessage::message_type: return std::make_unique<LoginRequestMessage>();
        case LoginResultMessage::message_type: return std::make_unique<LoginResultMessage>();
        case MessageResponseMessage::message_type: return std::make_unique<MessageResponseMessage>();
        case EndOfMessageMessage::message_type: return std::make_unique<EndOfMessageMessage>();
        default: return std::make_unique<UnknownTcpMessage>(code);
    }
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
