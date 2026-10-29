#include "MessageType.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SimpleInstrumentDefinitionMessage: return "Simple Instrument Definition Message";
        case MessageType::ComplexInstrumentDefinitionMessage: return "Complex Instrument Definition Message";
        case MessageType::SystemStateMessage: return "System State Message";
        case MessageType::InstrumentTradingStatusNotificationMessage: return "Instrument Trading Status Notification Message";
        case MessageType::BestBidAndOfferMessage: return "Best Bid And Offer Message";
        case MessageType::LastSaleMessage: return "Last Sale Message";
        case MessageType::TradeCancelMessage: return "Trade Cancel Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
