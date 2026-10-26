#include "MessageType.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SystemEventMessage: return "System Event Message";
        case MessageType::OptionsDirectoryMessage: return "Options Directory Message";
        case MessageType::TradingActionMessage: return "Trading Action Message";
        case MessageType::SecurityOpenMessage: return "Security Open Message";
        case MessageType::AddOrderMessageShortMessageForm: return "Add Order Message Short Message Form";
        case MessageType::AddOrderMessageLongFormMessage: return "Add Order Message Long Form Message";
        case MessageType::AddQuoteMessageShortFormMessage: return "Add Quote Message Short Form Message";
        case MessageType::AddQuoteMessageLongFormMessage: return "Add Quote Message Long Form Message";
        case MessageType::SingleSideExecutedMessage: return "Single Side Executed Message";
        case MessageType::SingleSideExecutedWithPriceMessage: return "Single Side Executed With Price Message";
        case MessageType::OrderCancelMessage: return "Order Cancel Message";
        case MessageType::SingleSideReplaceMessageShortForm: return "Single Side Replace Message Short Form";
        case MessageType::SingleSideReplaceMessageLongForm: return "Single Side Replace Message Long Form";
        case MessageType::SingleSideDeleteMessage: return "Single Side Delete Message";
        case MessageType::SingleSideChangeMessage: return "Single Side Change Message";
        case MessageType::QuoteReplaceMessageShortForm: return "Quote Replace Message Short Form";
        case MessageType::QuoteReplaceMessageLongForm: return "Quote Replace Message Long Form";
        case MessageType::QuoteDeleteMessage: return "Quote Delete Message";
        case MessageType::OptionsTradeMessagesNonAuction: return "Options Trade Messages Non Auction";
        case MessageType::OptionsCrossTradeMessage: return "Options Cross Trade Message";
        case MessageType::BrokenTradeOrderExecutedMessage: return "Broken Trade Order Executed Message";
        case MessageType::NoiiMessage: return "Noii Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
