#include "TemplateId.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

std::string_view to_string(TemplateId value) {
    switch (value) {
        case TemplateId::HeartbeatMessage: return "Heartbeat Message";
        case TemplateId::ProductSummaryMessage: return "Product Summary Message";
        case TemplateId::SnapshotOrderMessage: return "Snapshot Order Message";
        case TemplateId::InstrumentSummaryMessage: return "Instrument Summary Message";
        case TemplateId::AuctionBestBidOfferMessage: return "Auction Best Bid Offer Message";
        case TemplateId::AuctionClearingPriceMessage: return "Auction Clearing Price Message";
        case TemplateId::TopOfBookMessage: return "Top Of Book Message";
        case TemplateId::OrderAddMessage: return "Order Add Message";
        case TemplateId::OrderModifyMessage: return "Order Modify Message";
        case TemplateId::OrderModifySamePriorityMessage: return "Order Modify Same Priority Message";
        case TemplateId::OrderDeleteMessage: return "Order Delete Message";
        case TemplateId::OrderMassDeleteMessage: return "Order Mass Delete Message";
        case TemplateId::PartialOrderExecutionMessage: return "Partial Order Execution Message";
        case TemplateId::FullOrderExecutionMessage: return "Full Order Execution Message";
        case TemplateId::TradeReversalMessage: return "Trade Reversal Message";
        case TemplateId::ExecutionSummaryMessage: return "Execution Summary Message";
        case TemplateId::InstrumentInfoMessage: return "Instrument Info Message";
        case TemplateId::LppRangeMessage: return "Lpp Range Message";
        case TemplateId::ProductStateChangeMessage: return "Product State Change Message";
        case TemplateId::InstrumentStateChangeMessage: return "Instrument State Change Message";
        case TemplateId::AddComplexInstrumentMessage: return "Add Complex Instrument Message";
        case TemplateId::PacketHeader: return "Packet Header";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TemplateId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
