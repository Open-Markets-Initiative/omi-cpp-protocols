#include "Factory.hpp"

#include "definitions.hpp"

namespace nyse::arcaequities::bbo::xdp::v2_4_c {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SequenceNumberResetMessage::message_type: return std::make_unique<SequenceNumberResetMessage>();
        case SourceTimeReferenceMessage::message_type: return std::make_unique<SourceTimeReferenceMessage>();
        case SymbolIndexMappingMessage::message_type: return std::make_unique<SymbolIndexMappingMessage>();
        case RetransmissionRequestMessage::message_type: return std::make_unique<RetransmissionRequestMessage>();
        case RequestResponseMessage::message_type: return std::make_unique<RequestResponseMessage>();
        case HeartbeatResponseMessage::message_type: return std::make_unique<HeartbeatResponseMessage>();
        case SymbolIndexMappingRequestMessage::message_type: return std::make_unique<SymbolIndexMappingRequestMessage>();
        case RefreshRequestMessage::message_type: return std::make_unique<RefreshRequestMessage>();
        case MessageUnavailableMessage::message_type: return std::make_unique<MessageUnavailableMessage>();
        case SymbolClearMessage::message_type: return std::make_unique<SymbolClearMessage>();
        case TradingSessionChangeMessage::message_type: return std::make_unique<TradingSessionChangeMessage>();
        case SecurityStatusMessage::message_type: return std::make_unique<SecurityStatusMessage>();
        case RefreshHeaderMessage::message_type: return std::make_unique<RefreshHeaderMessage>();
        case QuoteMessage::message_type: return std::make_unique<QuoteMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace nyse::arcaequities::bbo::xdp::v2_4_c
