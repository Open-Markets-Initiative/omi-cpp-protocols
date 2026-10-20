#include "TemplateId.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

std::string_view to_string(TemplateId value) {
    switch (value) {
        case TemplateId::SequenceReset1Message: return "Sequence Reset 1 Message";
        case TemplateId::Sequence2Message: return "Sequence 2 Message";
        case TemplateId::EmptyBook9Message: return "Empty Book 9 Message";
        case TemplateId::ChannelReset11Message: return "Channel Reset 11 Message";
        case TemplateId::SecurityStatus3Message: return "Security Status 3 Message";
        case TemplateId::SecurityGroupPhase10Message: return "Security Group Phase 10 Message";
        case TemplateId::DeprecatedsecurityDefinitionMessage: return "DeprecatedSecurity Definition Message";
        case TemplateId::SecurityDefinitionMessage: return "Security Definition Message";
        case TemplateId::News5Message: return "News 5 Message";
        case TemplateId::OpeningPrice15Message: return "Opening Price 15 Message";
        case TemplateId::TheoreticalOpeningPrice16Message: return "Theoretical Opening Price 16 Message";
        case TemplateId::ClosingPrice17Message: return "Closing Price 17 Message";
        case TemplateId::AuctionImbalance19Message: return "Auction Imbalance 19 Message";
        case TemplateId::PriceBand20Message: return "Price Band 20 Message";
        case TemplateId::QuantityBand21Message: return "Quantity Band 21 Message";
        case TemplateId::PriceBand22Message: return "Price Band 22 Message";
        case TemplateId::HighPrice24Message: return "High Price 24 Message";
        case TemplateId::LowPrice25Message: return "Low Price 25 Message";
        case TemplateId::LastTradePrice27Message: return "Last Trade Price 27 Message";
        case TemplateId::SnapshotFullRefreshHeader30Message: return "Snapshot Full Refresh Header 30 Message";
        case TemplateId::OrderMbO50Message: return "Order Mb O 50 Message";
        case TemplateId::DeleteOrderMbO51Message: return "Delete Order Mb O 51 Message";
        case TemplateId::MassDeleteOrdersMbO52Message: return "Mass Delete Orders Mb O 52 Message";
        case TemplateId::Trade53Message: return "Trade 53 Message";
        case TemplateId::ForwardTrade54Message: return "Forward Trade 54 Message";
        case TemplateId::ExecutionSummary55Message: return "Execution Summary 55 Message";
        case TemplateId::ExecutionStatistics56Message: return "Execution Statistics 56 Message";
        case TemplateId::TradeBust57Message: return "Trade Bust 57 Message";
        case TemplateId::SnapshotFullRefreshOrdersMbO71Message: return "Snapshot Full Refresh Orders Mb O 71 Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TemplateId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
