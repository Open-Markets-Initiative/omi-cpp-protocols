#include "MessageType.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SecondsTimestampMessage: return "Seconds Timestamp Message";
        case MessageType::TradingStatusMessage: return "Trading Status Message";
        case MessageType::ExecutionSummaryMessage: return "Execution Summary Message";
        case MessageType::AddOrderMessage: return "Add Order Message";
        case MessageType::OrderExecutedMessage: return "Order Executed Message";
        case MessageType::OrderExecutedWithPriceMessage: return "Order Executed With Price Message";
        case MessageType::OrderDeleteMessage: return "Order Delete Message";
        case MessageType::ResetMessage: return "Reset Message";
        case MessageType::CommunicationControlMessage: return "Communication Control Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
