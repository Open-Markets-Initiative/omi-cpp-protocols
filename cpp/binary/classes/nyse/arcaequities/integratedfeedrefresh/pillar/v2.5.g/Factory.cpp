#include "Factory.hpp"

#include "definitions.hpp"

namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SequenceNumberResetMessage::message_type: return std::make_unique<SequenceNumberResetMessage>();
        case SourceTimeReferenceMessage::message_type: return std::make_unique<SourceTimeReferenceMessage>();
        case SymbolIndexMappingMessage::message_type: return std::make_unique<SymbolIndexMappingMessage>();
        case SecurityStatusMessage::message_type: return std::make_unique<SecurityStatusMessage>();
        case RefreshHeaderMessage::message_type: return std::make_unique<RefreshHeaderMessage>();
        case ImbalanceMessage::message_type: return std::make_unique<ImbalanceMessage>();
        case AddOrderRefreshMessage::message_type: return std::make_unique<AddOrderRefreshMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g
