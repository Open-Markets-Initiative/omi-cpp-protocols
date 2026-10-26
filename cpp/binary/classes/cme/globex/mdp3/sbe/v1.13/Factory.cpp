#include "Factory.hpp"

#include "definitions.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

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
        case SecurityStatus::message_type: return std::make_unique<SecurityStatus>();
        case MdIncrementalRefreshVolume::message_type: return std::make_unique<MdIncrementalRefreshVolume>();
        case QuoteRequest::message_type: return std::make_unique<QuoteRequest>();
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
        case MdInstrumentDefinitionFixedIncome::message_type: return std::make_unique<MdInstrumentDefinitionFixedIncome>();
        case MdInstrumentDefinitionRepo::message_type: return std::make_unique<MdInstrumentDefinitionRepo>();
        case SnapshotRefreshTopOrders::message_type: return std::make_unique<SnapshotRefreshTopOrders>();
        case SecurityStatusWorkup::message_type: return std::make_unique<SecurityStatusWorkup>();
        case SnapshotFullRefreshTcp::message_type: return std::make_unique<SnapshotFullRefreshTcp>();
        case CollateralMarketValue::message_type: return std::make_unique<CollateralMarketValue>();
        case MdInstrumentDefinitionFx::message_type: return std::make_unique<MdInstrumentDefinitionFx>();
        case MdIncrementalRefreshBookLongQty::message_type: return std::make_unique<MdIncrementalRefreshBookLongQty>();
        case MdIncrementalRefreshTradeSummaryLongQty::message_type: return std::make_unique<MdIncrementalRefreshTradeSummaryLongQty>();
        case MdIncrementalRefreshVolumeLongQty::message_type: return std::make_unique<MdIncrementalRefreshVolumeLongQty>();
        case MdIncrementalRefreshSessionStatisticsLongQty::message_type: return std::make_unique<MdIncrementalRefreshSessionStatisticsLongQty>();
        case SnapshotFullRefreshTcpLongQty::message_type: return std::make_unique<SnapshotFullRefreshTcpLongQty>();
        case SnapshotFullRefreshLongQty::message_type: return std::make_unique<SnapshotFullRefreshLongQty>();
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
        case ServerPayloadSecurityStatus::message_type: return std::make_unique<ServerPayloadSecurityStatus>();
        case ServerPayloadMdIncrementalRefreshVolume::message_type: return std::make_unique<ServerPayloadMdIncrementalRefreshVolume>();
        case ServerPayloadQuoteRequest::message_type: return std::make_unique<ServerPayloadQuoteRequest>();
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
        case ServerPayloadMdInstrumentDefinitionFixedIncome::message_type: return std::make_unique<ServerPayloadMdInstrumentDefinitionFixedIncome>();
        case ServerPayloadMdInstrumentDefinitionRepo::message_type: return std::make_unique<ServerPayloadMdInstrumentDefinitionRepo>();
        case ServerPayloadSnapshotRefreshTopOrders::message_type: return std::make_unique<ServerPayloadSnapshotRefreshTopOrders>();
        case ServerPayloadSecurityStatusWorkup::message_type: return std::make_unique<ServerPayloadSecurityStatusWorkup>();
        case ServerPayloadSnapshotFullRefreshTcp::message_type: return std::make_unique<ServerPayloadSnapshotFullRefreshTcp>();
        case ServerPayloadCollateralMarketValue::message_type: return std::make_unique<ServerPayloadCollateralMarketValue>();
        case ServerPayloadMdInstrumentDefinitionFx::message_type: return std::make_unique<ServerPayloadMdInstrumentDefinitionFx>();
        case ServerPayloadMdIncrementalRefreshBookLongQty::message_type: return std::make_unique<ServerPayloadMdIncrementalRefreshBookLongQty>();
        case ServerPayloadMdIncrementalRefreshTradeSummaryLongQty::message_type: return std::make_unique<ServerPayloadMdIncrementalRefreshTradeSummaryLongQty>();
        case ServerPayloadMdIncrementalRefreshVolumeLongQty::message_type: return std::make_unique<ServerPayloadMdIncrementalRefreshVolumeLongQty>();
        case ServerPayloadMdIncrementalRefreshSessionStatisticsLongQty::message_type: return std::make_unique<ServerPayloadMdIncrementalRefreshSessionStatisticsLongQty>();
        case ServerPayloadSnapshotFullRefreshTcpLongQty::message_type: return std::make_unique<ServerPayloadSnapshotFullRefreshTcpLongQty>();
        case ServerPayloadSnapshotFullRefreshLongQty::message_type: return std::make_unique<ServerPayloadSnapshotFullRefreshLongQty>();
        case ServerPayloadNegotiationReject::message_type: return std::make_unique<ServerPayloadNegotiationReject>();
        case ServerPayloadNegotiationResponse::message_type: return std::make_unique<ServerPayloadNegotiationResponse>();
        case ServerPayloadTerminate::message_type: return std::make_unique<ServerPayloadTerminate>();
        case ServerPayloadRequestAck::message_type: return std::make_unique<ServerPayloadRequestAck>();
        case ServerPayloadRequestReject::message_type: return std::make_unique<ServerPayloadRequestReject>();
        default: return std::make_unique<UnknownServerTcpMessage>(code);
    }
}

} // namespace cme::globex::mdp3::sbe::v1_13
