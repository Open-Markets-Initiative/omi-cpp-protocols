#include "Factory.hpp"

#include "definitions.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case MktdataMessage::message_type: return std::make_unique<MktdataMessage>();
        case MdpsessionmgmtMessage::message_type: return std::make_unique<MdpsessionmgmtMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

std::unique_ptr<MktdataPayload> MktdataPayloadFactory::create(MktdataPayloadCode code) {
    switch (code) {
        case ChannelReset::message_type: return std::make_unique<ChannelReset>();
        case AdminHeartbeat::message_type: return std::make_unique<AdminHeartbeat>();
        case AdminLogin::message_type: return std::make_unique<AdminLogin>();
        case AdminLogout::message_type: return std::make_unique<AdminLogout>();
        case MdInstrumentDefinitionFutureLegacy::message_type: return std::make_unique<MdInstrumentDefinitionFutureLegacy>();
        case MdInstrumentDefinitionSpreadLegacy::message_type: return std::make_unique<MdInstrumentDefinitionSpreadLegacy>();
        case SecurityStatus::message_type: return std::make_unique<SecurityStatus>();
        case MdIncrementalRefreshBookLegacy::message_type: return std::make_unique<MdIncrementalRefreshBookLegacy>();
        case MdIncrementalRefreshDailyStatisticsLegacy::message_type: return std::make_unique<MdIncrementalRefreshDailyStatisticsLegacy>();
        case MdIncrementalRefreshLimitsBandingLegacy::message_type: return std::make_unique<MdIncrementalRefreshLimitsBandingLegacy>();
        case MdIncrementalRefreshSessionStatisticsLegacy::message_type: return std::make_unique<MdIncrementalRefreshSessionStatisticsLegacy>();
        case MdIncrementalRefreshVolume::message_type: return std::make_unique<MdIncrementalRefreshVolume>();
        case SnapshotFullRefreshLegacy::message_type: return std::make_unique<SnapshotFullRefreshLegacy>();
        case QuoteRequest::message_type: return std::make_unique<QuoteRequest>();
        case MdInstrumentDefinitionOptionLegacy::message_type: return std::make_unique<MdInstrumentDefinitionOptionLegacy>();
        case MdIncrementalRefreshTradeSummaryLegacy::message_type: return std::make_unique<MdIncrementalRefreshTradeSummaryLegacy>();
        case MdIncrementalRefreshOrderBookLegacy::message_type: return std::make_unique<MdIncrementalRefreshOrderBookLegacy>();
        case SnapshotFullRefreshOrderBookLegacy::message_type: return std::make_unique<SnapshotFullRefreshOrderBookLegacy>();
        case MdIncrementalRefreshBook::message_type: return std::make_unique<MdIncrementalRefreshBook>();
        case MdIncrementalRefreshOrderBook::message_type: return std::make_unique<MdIncrementalRefreshOrderBook>();
        case MdIncrementalRefreshTradeSummary::message_type: return std::make_unique<MdIncrementalRefreshTradeSummary>();
        case MdIncrementalRefreshDailyStatistics::message_type: return std::make_unique<MdIncrementalRefreshDailyStatistics>();
        case MdIncrementalRefreshLimitsBanding::message_type: return std::make_unique<MdIncrementalRefreshLimitsBanding>();
        case MdIncrementalRefreshSessionStatistics::message_type: return std::make_unique<MdIncrementalRefreshSessionStatistics>();
        case SnapshotFullRefresh::message_type: return std::make_unique<SnapshotFullRefresh>();
        case SnapshotFullRefreshOrderBook::message_type: return std::make_unique<SnapshotFullRefreshOrderBook>();
        case MdInstrumentDefinitionFuture::message_type: return std::make_unique<MdInstrumentDefinitionFuture>();
        case MdInstrumentDefinitionOption::message_type: return std::make_unique<MdInstrumentDefinitionOption>();
        case MdInstrumentDefinitionSpread::message_type: return std::make_unique<MdInstrumentDefinitionSpread>();
        default: return std::make_unique<UnknownMktdataPayload>(code);
    }
}

std::unique_ptr<MdpsessionmgmtPayload> MdpsessionmgmtPayloadFactory::create(MdpsessionmgmtPayloadCode code) {
    switch (code) {
        case Negotiate::message_type: return std::make_unique<Negotiate>();
        case NegotiationReject::message_type: return std::make_unique<NegotiationReject>();
        case NegotiationResponse::message_type: return std::make_unique<NegotiationResponse>();
        case Terminate::message_type: return std::make_unique<Terminate>();
        case MarketDataRequest::message_type: return std::make_unique<MarketDataRequest>();
        case RequestAck::message_type: return std::make_unique<RequestAck>();
        case RequestReject::message_type: return std::make_unique<RequestReject>();
        case SecurityListRequest::message_type: return std::make_unique<SecurityListRequest>();
        case SecurityStatusRequest::message_type: return std::make_unique<SecurityStatusRequest>();
        case SubscriberHeartbeat::message_type: return std::make_unique<SubscriberHeartbeat>();
        default: return std::make_unique<UnknownMdpsessionmgmtPayload>(code);
    }
}

std::unique_ptr<ClientTcpMessage> ClientTcpMessageFactory::create(ClientTcpMessageCode code) {
    switch (code) {
        case ClientPayloadNegotiate::message_type: return std::make_unique<ClientPayloadNegotiate>();
        case ClientPayloadTerminate::message_type: return std::make_unique<ClientPayloadTerminate>();
        case ClientPayloadMarketDataRequest::message_type: return std::make_unique<ClientPayloadMarketDataRequest>();
        case ClientPayloadSecurityListRequest::message_type: return std::make_unique<ClientPayloadSecurityListRequest>();
        case ClientPayloadSecurityStatusRequest::message_type: return std::make_unique<ClientPayloadSecurityStatusRequest>();
        default: return std::make_unique<UnknownClientTcpMessage>(code);
    }
}

std::unique_ptr<ServerTcpMessage> ServerTcpMessageFactory::create(ServerTcpMessageCode code) {
    switch (code) {
        case ServerPayloadChannelReset::message_type: return std::make_unique<ServerPayloadChannelReset>();
        case ServerPayloadAdminLogin::message_type: return std::make_unique<ServerPayloadAdminLogin>();
        case ServerPayloadAdminLogout::message_type: return std::make_unique<ServerPayloadAdminLogout>();
        case ServerPayloadMdInstrumentDefinitionFutureLegacy::message_type: return std::make_unique<ServerPayloadMdInstrumentDefinitionFutureLegacy>();
        case ServerPayloadMdInstrumentDefinitionSpreadLegacy::message_type: return std::make_unique<ServerPayloadMdInstrumentDefinitionSpreadLegacy>();
        case ServerPayloadSecurityStatus::message_type: return std::make_unique<ServerPayloadSecurityStatus>();
        case ServerPayloadMdIncrementalRefreshBookLegacy::message_type: return std::make_unique<ServerPayloadMdIncrementalRefreshBookLegacy>();
        case ServerPayloadMdIncrementalRefreshDailyStatisticsLegacy::message_type: return std::make_unique<ServerPayloadMdIncrementalRefreshDailyStatisticsLegacy>();
        case ServerPayloadMdIncrementalRefreshLimitsBandingLegacy::message_type: return std::make_unique<ServerPayloadMdIncrementalRefreshLimitsBandingLegacy>();
        case ServerPayloadMdIncrementalRefreshSessionStatisticsLegacy::message_type: return std::make_unique<ServerPayloadMdIncrementalRefreshSessionStatisticsLegacy>();
        case ServerPayloadMdIncrementalRefreshVolume::message_type: return std::make_unique<ServerPayloadMdIncrementalRefreshVolume>();
        case ServerPayloadSnapshotFullRefreshLegacy::message_type: return std::make_unique<ServerPayloadSnapshotFullRefreshLegacy>();
        case ServerPayloadQuoteRequest::message_type: return std::make_unique<ServerPayloadQuoteRequest>();
        case ServerPayloadMdInstrumentDefinitionOptionLegacy::message_type: return std::make_unique<ServerPayloadMdInstrumentDefinitionOptionLegacy>();
        case ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::message_type: return std::make_unique<ServerPayloadMdIncrementalRefreshTradeSummaryLegacy>();
        case ServerPayloadMdIncrementalRefreshOrderBookLegacy::message_type: return std::make_unique<ServerPayloadMdIncrementalRefreshOrderBookLegacy>();
        case ServerPayloadSnapshotFullRefreshOrderBookLegacy::message_type: return std::make_unique<ServerPayloadSnapshotFullRefreshOrderBookLegacy>();
        case ServerPayloadMdIncrementalRefreshBook::message_type: return std::make_unique<ServerPayloadMdIncrementalRefreshBook>();
        case ServerPayloadMdIncrementalRefreshOrderBook::message_type: return std::make_unique<ServerPayloadMdIncrementalRefreshOrderBook>();
        case ServerPayloadMdIncrementalRefreshTradeSummary::message_type: return std::make_unique<ServerPayloadMdIncrementalRefreshTradeSummary>();
        case ServerPayloadMdIncrementalRefreshDailyStatistics::message_type: return std::make_unique<ServerPayloadMdIncrementalRefreshDailyStatistics>();
        case ServerPayloadMdIncrementalRefreshLimitsBanding::message_type: return std::make_unique<ServerPayloadMdIncrementalRefreshLimitsBanding>();
        case ServerPayloadMdIncrementalRefreshSessionStatistics::message_type: return std::make_unique<ServerPayloadMdIncrementalRefreshSessionStatistics>();
        case ServerPayloadSnapshotFullRefresh::message_type: return std::make_unique<ServerPayloadSnapshotFullRefresh>();
        case ServerPayloadSnapshotFullRefreshOrderBook::message_type: return std::make_unique<ServerPayloadSnapshotFullRefreshOrderBook>();
        case ServerPayloadMdInstrumentDefinitionFuture::message_type: return std::make_unique<ServerPayloadMdInstrumentDefinitionFuture>();
        case ServerPayloadMdInstrumentDefinitionOption::message_type: return std::make_unique<ServerPayloadMdInstrumentDefinitionOption>();
        case ServerPayloadMdInstrumentDefinitionSpread::message_type: return std::make_unique<ServerPayloadMdInstrumentDefinitionSpread>();
        case ServerPayloadNegotiationReject::message_type: return std::make_unique<ServerPayloadNegotiationReject>();
        case ServerPayloadNegotiationResponse::message_type: return std::make_unique<ServerPayloadNegotiationResponse>();
        case ServerPayloadTerminate::message_type: return std::make_unique<ServerPayloadTerminate>();
        case ServerPayloadRequestAck::message_type: return std::make_unique<ServerPayloadRequestAck>();
        case ServerPayloadRequestReject::message_type: return std::make_unique<ServerPayloadRequestReject>();
        default: return std::make_unique<UnknownServerTcpMessage>(code);
    }
}

} // namespace cme::globex::mdp3::sbe::v1_9
