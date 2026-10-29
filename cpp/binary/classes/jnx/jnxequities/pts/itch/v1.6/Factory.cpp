#include "Factory.hpp"

#include "definitions.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SecondsMessage::message_type: return std::make_unique<SecondsMessage>();
        case SystemEventMessage::message_type: return std::make_unique<SystemEventMessage>();
        case PriceTickSizeMessage::message_type: return std::make_unique<PriceTickSizeMessage>();
        case OrderbookDirectoryMessage::message_type: return std::make_unique<OrderbookDirectoryMessage>();
        case TradingStateMessage::message_type: return std::make_unique<TradingStateMessage>();
        case ShortSellingPriceRestrictionStateMessage::message_type: return std::make_unique<ShortSellingPriceRestrictionStateMessage>();
        case OrderAddedWithoutAttributesMessage::message_type: return std::make_unique<OrderAddedWithoutAttributesMessage>();
        case OrderAddedWithAttributesMessage::message_type: return std::make_unique<OrderAddedWithAttributesMessage>();
        case OrderExecutedMessage::message_type: return std::make_unique<OrderExecutedMessage>();
        case OrderDeletedMessage::message_type: return std::make_unique<OrderDeletedMessage>();
        case OrderReplacedMessage::message_type: return std::make_unique<OrderReplacedMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace jnx::jnxequities::pts::itch::v1_6
