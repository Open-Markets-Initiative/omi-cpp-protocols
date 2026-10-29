#include "TemplateId.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

std::string_view to_string(TemplateId value) {
    switch (value) {
        case TemplateId::AddComplexInstrument: return "Add Complex Instrument";
        case TemplateId::AuctionBbo: return "Auction Bbo";
        case TemplateId::AuctionClearingPrice: return "Auction Clearing Price";
        case TemplateId::CrossRequest: return "Cross Request";
        case TemplateId::ExecutionSummary: return "Execution Summary";
        case TemplateId::FullOrderExecution: return "Full Order Execution";
        case TemplateId::Heartbeat: return "Heartbeat";
        case TemplateId::InstrumentStateChange: return "Instrument State Change";
        case TemplateId::InstrumentSummary: return "Instrument Summary";
        case TemplateId::OrderAdd: return "Order Add";
        case TemplateId::OrderDelete: return "Order Delete";
        case TemplateId::OrderMassDelete: return "Order Mass Delete";
        case TemplateId::OrderModify: return "Order Modify";
        case TemplateId::OrderModifySamePrio: return "Order Modify Same Prio";
        case TemplateId::PacketHeader: return "Packet Header";
        case TemplateId::PartialOrderExecution: return "Partial Order Execution";
        case TemplateId::ProductStateChange: return "Product State Change";
        case TemplateId::ProductSummary: return "Product Summary";
        case TemplateId::QuoteRequest: return "Quote Request";
        case TemplateId::SnapshotOrder: return "Snapshot Order";
        case TemplateId::TopOfBook: return "Top Of Book";
        case TemplateId::TradeReport: return "Trade Report";
        case TemplateId::TradeReversal: return "Trade Reversal";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TemplateId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v3_0
