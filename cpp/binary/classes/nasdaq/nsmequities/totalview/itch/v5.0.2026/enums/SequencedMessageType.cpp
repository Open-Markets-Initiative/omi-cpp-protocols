#include "SequencedMessageType.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

std::string_view to_string(SequencedMessageType value) {
    switch (value) {
        case SequencedMessageType::SystemEventMessage: return "System Event Message";
        case SequencedMessageType::StockDirectoryMessage: return "Stock Directory Message";
        case SequencedMessageType::StockTradingActionMessage: return "Stock Trading Action Message";
        case SequencedMessageType::RegShoShortSalePriceTestRestrictedIndicatorMessage: return "Reg Sho Short Sale Price Test Restricted Indicator Message";
        case SequencedMessageType::MarketParticipantPositionMessage: return "Market Participant Position Message";
        case SequencedMessageType::MwcbDeclineLevelMessage: return "Mwcb Decline Level Message";
        case SequencedMessageType::MwcbStatusLevelMessage: return "Mwcb Status Level Message";
        case SequencedMessageType::IpoQuotingPeriodUpdate: return "Ipo Quoting Period Update";
        case SequencedMessageType::LuldAuctionCollarMessage: return "Luld Auction Collar Message";
        case SequencedMessageType::OperationalHaltMessage: return "Operational Halt Message";
        case SequencedMessageType::AddOrderNoMpidAttributionMessage: return "Add Order No Mpid Attribution Message";
        case SequencedMessageType::AddOrderWithMpidAttributionMessage: return "Add Order With Mpid Attribution Message";
        case SequencedMessageType::OrderExecutedMessage: return "Order Executed Message";
        case SequencedMessageType::OrderExecutedWithPriceMessage: return "Order Executed With Price Message";
        case SequencedMessageType::OrderCancelMessage: return "Order Cancel Message";
        case SequencedMessageType::OrderDeleteMessage: return "Order Delete Message";
        case SequencedMessageType::OrderReplaceMessage: return "Order Replace Message";
        case SequencedMessageType::NonCrossTradeMessage: return "Non Cross Trade Message";
        case SequencedMessageType::CrossTradeMessage: return "Cross Trade Message";
        case SequencedMessageType::BrokenTradeMessage: return "Broken Trade Message";
        case SequencedMessageType::NetOrderImbalanceIndicatorMessage: return "Net Order Imbalance Indicator Message";
        case SequencedMessageType::RetailPriceImprovementIndicatorMessage: return "Retail Price Improvement Indicator Message";
        case SequencedMessageType::DirectListingWithCapitalRaisePriceDiscoveryMessage: return "Direct Listing With Capital Raise Price Discovery Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SequencedMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2026
