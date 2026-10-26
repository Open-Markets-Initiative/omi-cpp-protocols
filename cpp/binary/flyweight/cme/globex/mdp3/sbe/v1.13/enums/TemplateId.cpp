#include "TemplateId.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

std::string_view to_string(TemplateId value) {
    switch (value) {
        case TemplateId::ChannelReset: return "Channel Reset";
        case TemplateId::AdminHeartbeat: return "Admin Heartbeat";
        case TemplateId::AdminLogin: return "Admin Login";
        case TemplateId::AdminLogout: return "Admin Logout";
        case TemplateId::SecurityStatus: return "Security Status";
        case TemplateId::MdIncrementalRefreshVolume: return "Md Incremental Refresh Volume";
        case TemplateId::QuoteRequest: return "Quote Request";
        case TemplateId::MdIncrementalRefreshBook: return "Md Incremental Refresh Book";
        case TemplateId::MdIncrementalRefreshOrderBook: return "Md Incremental Refresh Order Book";
        case TemplateId::MdIncrementalRefreshTradeSummary: return "Md Incremental Refresh Trade Summary";
        case TemplateId::MdIncrementalRefreshDailyStatistics: return "Md Incremental Refresh Daily Statistics";
        case TemplateId::MdIncrementalRefreshLimitsBanding: return "Md Incremental Refresh Limits Banding";
        case TemplateId::MdIncrementalRefreshSessionStatistics: return "Md Incremental Refresh Session Statistics";
        case TemplateId::SnapshotFullRefresh: return "Snapshot Full Refresh";
        case TemplateId::SnapshotFullRefreshOrderBook: return "Snapshot Full Refresh Order Book";
        case TemplateId::MdInstrumentDefinitionFuture: return "Md Instrument Definition Future";
        case TemplateId::MdInstrumentDefinitionOption: return "Md Instrument Definition Option";
        case TemplateId::MdInstrumentDefinitionSpread: return "Md Instrument Definition Spread";
        case TemplateId::MdInstrumentDefinitionFixedIncome: return "Md Instrument Definition Fixed Income";
        case TemplateId::MdInstrumentDefinitionRepo: return "Md Instrument Definition Repo";
        case TemplateId::SnapshotRefreshTopOrders: return "Snapshot Refresh Top Orders";
        case TemplateId::SecurityStatusWorkup: return "Security Status Workup";
        case TemplateId::SnapshotFullRefreshTcp: return "Snapshot Full Refresh Tcp";
        case TemplateId::CollateralMarketValue: return "Collateral Market Value";
        case TemplateId::MdInstrumentDefinitionFx: return "Md Instrument Definition Fx";
        case TemplateId::MdIncrementalRefreshBookLongQty: return "Md Incremental Refresh Book Long Qty";
        case TemplateId::MdIncrementalRefreshTradeSummaryLongQty: return "Md Incremental Refresh Trade Summary Long Qty";
        case TemplateId::MdIncrementalRefreshVolumeLongQty: return "Md Incremental Refresh Volume Long Qty";
        case TemplateId::MdIncrementalRefreshSessionStatisticsLongQty: return "Md Incremental Refresh Session Statistics Long Qty";
        case TemplateId::SnapshotFullRefreshTcpLongQty: return "Snapshot Full Refresh Tcp Long Qty";
        case TemplateId::SnapshotFullRefreshLongQty: return "Snapshot Full Refresh Long Qty";
        case TemplateId::Negotiate: return "Negotiate";
        case TemplateId::NegotiationReject: return "Negotiation Reject";
        case TemplateId::NegotiationResponse: return "Negotiation Response";
        case TemplateId::Terminate: return "Terminate";
        case TemplateId::MarketDataRequest: return "Market Data Request";
        case TemplateId::RequestAck: return "Request Ack";
        case TemplateId::RequestReject: return "Request Reject";
        case TemplateId::SecurityListRequest: return "Security List Request";
        case TemplateId::SecurityStatusRequest: return "Security Status Request";
        case TemplateId::SubscriberHeartbeat: return "Subscriber Heartbeat";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TemplateId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_13
