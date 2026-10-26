#pragma once

namespace cme::globex::mdp3::sbe::v1_13 {

class MktdataMessage;
class MdpsessionmgmtMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const MktdataMessage&) {}
    virtual void visit(const MdpsessionmgmtMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

class ChannelReset;
class AdminHeartbeat;
class AdminLogin;
class AdminLogout;
class SecurityStatus;
class MdIncrementalRefreshVolume;
class QuoteRequest;
class MdIncrementalRefreshBook;
class MdIncrementalRefreshOrderBook;
class MdIncrementalRefreshTradeSummary;
class MdIncrementalRefreshDailyStatistics;
class MdIncrementalRefreshLimitsBanding;
class MdIncrementalRefreshSessionStatistics;
class SnapshotFullRefresh;
class SnapshotFullRefreshOrderBook;
class MdInstrumentDefinitionFuture;
class MdInstrumentDefinitionOption;
class MdInstrumentDefinitionSpread;
class MdInstrumentDefinitionFixedIncome;
class MdInstrumentDefinitionRepo;
class SnapshotRefreshTopOrders;
class SecurityStatusWorkup;
class SnapshotFullRefreshTcp;
class CollateralMarketValue;
class MdInstrumentDefinitionFx;
class MdIncrementalRefreshBookLongQty;
class MdIncrementalRefreshTradeSummaryLongQty;
class MdIncrementalRefreshVolumeLongQty;
class MdIncrementalRefreshSessionStatisticsLongQty;
class SnapshotFullRefreshTcpLongQty;
class SnapshotFullRefreshLongQty;
class UnknownMktdataPayload;

// What the messages of the Mktdata Payload dispatch are handed to,
// reached through the mktdata_payload a MktdataMessage holds.
class MktdataPayloadVisitor {
  public:
    virtual ~MktdataPayloadVisitor() = default;

    virtual void visit(const ChannelReset&) {}
    virtual void visit(const AdminHeartbeat&) {}
    virtual void visit(const AdminLogin&) {}
    virtual void visit(const AdminLogout&) {}
    virtual void visit(const SecurityStatus&) {}
    virtual void visit(const MdIncrementalRefreshVolume&) {}
    virtual void visit(const QuoteRequest&) {}
    virtual void visit(const MdIncrementalRefreshBook&) {}
    virtual void visit(const MdIncrementalRefreshOrderBook&) {}
    virtual void visit(const MdIncrementalRefreshTradeSummary&) {}
    virtual void visit(const MdIncrementalRefreshDailyStatistics&) {}
    virtual void visit(const MdIncrementalRefreshLimitsBanding&) {}
    virtual void visit(const MdIncrementalRefreshSessionStatistics&) {}
    virtual void visit(const SnapshotFullRefresh&) {}
    virtual void visit(const SnapshotFullRefreshOrderBook&) {}
    virtual void visit(const MdInstrumentDefinitionFuture&) {}
    virtual void visit(const MdInstrumentDefinitionOption&) {}
    virtual void visit(const MdInstrumentDefinitionSpread&) {}
    virtual void visit(const MdInstrumentDefinitionFixedIncome&) {}
    virtual void visit(const MdInstrumentDefinitionRepo&) {}
    virtual void visit(const SnapshotRefreshTopOrders&) {}
    virtual void visit(const SecurityStatusWorkup&) {}
    virtual void visit(const SnapshotFullRefreshTcp&) {}
    virtual void visit(const CollateralMarketValue&) {}
    virtual void visit(const MdInstrumentDefinitionFx&) {}
    virtual void visit(const MdIncrementalRefreshBookLongQty&) {}
    virtual void visit(const MdIncrementalRefreshTradeSummaryLongQty&) {}
    virtual void visit(const MdIncrementalRefreshVolumeLongQty&) {}
    virtual void visit(const MdIncrementalRefreshSessionStatisticsLongQty&) {}
    virtual void visit(const SnapshotFullRefreshTcpLongQty&) {}
    virtual void visit(const SnapshotFullRefreshLongQty&) {}
    virtual void visit(const UnknownMktdataPayload&) {}
};

class Negotiate;
class NegotiationReject;
class NegotiationResponse;
class Terminate;
class MarketDataRequest;
class RequestAck;
class RequestReject;
class SecurityListRequest;
class SecurityStatusRequest;
class SubscriberHeartbeat;
class UnknownMdpsessionmgmtPayload;

// What the messages of the Mdpsessionmgmt Payload dispatch are handed to,
// reached through the mdpsessionmgmt_payload a MdpsessionmgmtMessage holds.
class MdpsessionmgmtPayloadVisitor {
  public:
    virtual ~MdpsessionmgmtPayloadVisitor() = default;

    virtual void visit(const Negotiate&) {}
    virtual void visit(const NegotiationReject&) {}
    virtual void visit(const NegotiationResponse&) {}
    virtual void visit(const Terminate&) {}
    virtual void visit(const MarketDataRequest&) {}
    virtual void visit(const RequestAck&) {}
    virtual void visit(const RequestReject&) {}
    virtual void visit(const SecurityListRequest&) {}
    virtual void visit(const SecurityStatusRequest&) {}
    virtual void visit(const SubscriberHeartbeat&) {}
    virtual void visit(const UnknownMdpsessionmgmtPayload&) {}
};

class ClientPayloadNegotiate;
class ClientPayloadTerminate;
class ClientPayloadMarketDataRequest;
class ClientPayloadSecurityListRequest;
class ClientPayloadSecurityStatusRequest;
class UnknownClientTcpMessage;

// What the messages of the Client Payload dispatch are handed to,
// reached through the client_payload a ClientTcpMessage holds.
class ClientTcpMessageVisitor {
  public:
    virtual ~ClientTcpMessageVisitor() = default;

    virtual void visit(const ClientPayloadNegotiate&) {}
    virtual void visit(const ClientPayloadTerminate&) {}
    virtual void visit(const ClientPayloadMarketDataRequest&) {}
    virtual void visit(const ClientPayloadSecurityListRequest&) {}
    virtual void visit(const ClientPayloadSecurityStatusRequest&) {}
    virtual void visit(const UnknownClientTcpMessage&) {}
};

class ServerPayloadChannelReset;
class ServerPayloadAdminLogin;
class ServerPayloadAdminLogout;
class ServerPayloadSecurityStatus;
class ServerPayloadMdIncrementalRefreshVolume;
class ServerPayloadQuoteRequest;
class ServerPayloadMdIncrementalRefreshBook;
class ServerPayloadMdIncrementalRefreshOrderBook;
class ServerPayloadMdIncrementalRefreshTradeSummary;
class ServerPayloadMdIncrementalRefreshDailyStatistics;
class ServerPayloadMdIncrementalRefreshLimitsBanding;
class ServerPayloadMdIncrementalRefreshSessionStatistics;
class ServerPayloadSnapshotFullRefresh;
class ServerPayloadSnapshotFullRefreshOrderBook;
class ServerPayloadMdInstrumentDefinitionFuture;
class ServerPayloadMdInstrumentDefinitionOption;
class ServerPayloadMdInstrumentDefinitionSpread;
class ServerPayloadMdInstrumentDefinitionFixedIncome;
class ServerPayloadMdInstrumentDefinitionRepo;
class ServerPayloadSnapshotRefreshTopOrders;
class ServerPayloadSecurityStatusWorkup;
class ServerPayloadSnapshotFullRefreshTcp;
class ServerPayloadCollateralMarketValue;
class ServerPayloadMdInstrumentDefinitionFx;
class ServerPayloadMdIncrementalRefreshBookLongQty;
class ServerPayloadMdIncrementalRefreshTradeSummaryLongQty;
class ServerPayloadMdIncrementalRefreshVolumeLongQty;
class ServerPayloadMdIncrementalRefreshSessionStatisticsLongQty;
class ServerPayloadSnapshotFullRefreshTcpLongQty;
class ServerPayloadSnapshotFullRefreshLongQty;
class ServerPayloadNegotiationReject;
class ServerPayloadNegotiationResponse;
class ServerPayloadTerminate;
class ServerPayloadRequestAck;
class ServerPayloadRequestReject;
class UnknownServerTcpMessage;

// What the messages of the Server Payload dispatch are handed to,
// reached through the server_payload a ServerTcpMessage holds.
class ServerTcpMessageVisitor {
  public:
    virtual ~ServerTcpMessageVisitor() = default;

    virtual void visit(const ServerPayloadChannelReset&) {}
    virtual void visit(const ServerPayloadAdminLogin&) {}
    virtual void visit(const ServerPayloadAdminLogout&) {}
    virtual void visit(const ServerPayloadSecurityStatus&) {}
    virtual void visit(const ServerPayloadMdIncrementalRefreshVolume&) {}
    virtual void visit(const ServerPayloadQuoteRequest&) {}
    virtual void visit(const ServerPayloadMdIncrementalRefreshBook&) {}
    virtual void visit(const ServerPayloadMdIncrementalRefreshOrderBook&) {}
    virtual void visit(const ServerPayloadMdIncrementalRefreshTradeSummary&) {}
    virtual void visit(const ServerPayloadMdIncrementalRefreshDailyStatistics&) {}
    virtual void visit(const ServerPayloadMdIncrementalRefreshLimitsBanding&) {}
    virtual void visit(const ServerPayloadMdIncrementalRefreshSessionStatistics&) {}
    virtual void visit(const ServerPayloadSnapshotFullRefresh&) {}
    virtual void visit(const ServerPayloadSnapshotFullRefreshOrderBook&) {}
    virtual void visit(const ServerPayloadMdInstrumentDefinitionFuture&) {}
    virtual void visit(const ServerPayloadMdInstrumentDefinitionOption&) {}
    virtual void visit(const ServerPayloadMdInstrumentDefinitionSpread&) {}
    virtual void visit(const ServerPayloadMdInstrumentDefinitionFixedIncome&) {}
    virtual void visit(const ServerPayloadMdInstrumentDefinitionRepo&) {}
    virtual void visit(const ServerPayloadSnapshotRefreshTopOrders&) {}
    virtual void visit(const ServerPayloadSecurityStatusWorkup&) {}
    virtual void visit(const ServerPayloadSnapshotFullRefreshTcp&) {}
    virtual void visit(const ServerPayloadCollateralMarketValue&) {}
    virtual void visit(const ServerPayloadMdInstrumentDefinitionFx&) {}
    virtual void visit(const ServerPayloadMdIncrementalRefreshBookLongQty&) {}
    virtual void visit(const ServerPayloadMdIncrementalRefreshTradeSummaryLongQty&) {}
    virtual void visit(const ServerPayloadMdIncrementalRefreshVolumeLongQty&) {}
    virtual void visit(const ServerPayloadMdIncrementalRefreshSessionStatisticsLongQty&) {}
    virtual void visit(const ServerPayloadSnapshotFullRefreshTcpLongQty&) {}
    virtual void visit(const ServerPayloadSnapshotFullRefreshLongQty&) {}
    virtual void visit(const ServerPayloadNegotiationReject&) {}
    virtual void visit(const ServerPayloadNegotiationResponse&) {}
    virtual void visit(const ServerPayloadTerminate&) {}
    virtual void visit(const ServerPayloadRequestAck&) {}
    virtual void visit(const ServerPayloadRequestReject&) {}
    virtual void visit(const UnknownServerTcpMessage&) {}
};

} // namespace cme::globex::mdp3::sbe::v1_13
