#include "Factory.hpp"

#include "definitions.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SequenceNumberResetMessage::message_type: return std::make_unique<SequenceNumberResetMessage>();
        case SymbolIndexMappingMessage::message_type: return std::make_unique<SymbolIndexMappingMessage>();
        case RetransmissionRequestMessage::message_type: return std::make_unique<RetransmissionRequestMessage>();
        case RequestResponseMessage::message_type: return std::make_unique<RequestResponseMessage>();
        case HeartbeatResponseMessage::message_type: return std::make_unique<HeartbeatResponseMessage>();
        case SymbolIndexMappingRequestMessage::message_type: return std::make_unique<SymbolIndexMappingRequestMessage>();
        case RefreshRequestMessage::message_type: return std::make_unique<RefreshRequestMessage>();
        case MessageUnavailableMessage::message_type: return std::make_unique<MessageUnavailableMessage>();
        case SymbolClearMessage::message_type: return std::make_unique<SymbolClearMessage>();
        case SecurityStatusMessage::message_type: return std::make_unique<SecurityStatusMessage>();
        case RefreshHeaderMessage::message_type: return std::make_unique<RefreshHeaderMessage>();
        case ImbalanceMessage::message_type: return std::make_unique<ImbalanceMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a
