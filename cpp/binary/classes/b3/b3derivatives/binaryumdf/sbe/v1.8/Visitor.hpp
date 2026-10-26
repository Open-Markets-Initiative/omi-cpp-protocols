#pragma once

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

class SequenceMessage;
class EmptyBookMessage;
class ChannelReset11Message;
class SecurityStatus3Message;
class SecurityGroupPhase10Message;
class DeprecatedSecurityDefinitionMessage;
class SecurityDefinitionMessage;
class News5Message;
class OpeningPrice15Message;
class TheoreticalOpeningPrice16Message;
class ClosingPrice17Message;
class AuctionImbalance19Message;
class PriceBand20Message;
class QuantityBand21Message;
class PriceBand22Message;
class HighPrice24Message;
class LowPrice25Message;
class LastTradePrice27Message;
class SettlementPrice28Message;
class OpenInterest29Message;
class SnapshotFullRefreshHeader30Message;
class OrderMbO50Message;
class DeleteOrderMbO51Message;
class MassDeleteOrdersMbO52Message;
class Trade53Message;
class ForwardTrade54Message;
class ExecutionSummary55Message;
class ExecutionStatistics56Message;
class TradeBust57Message;
class SnapshotFullRefreshOrdersMbO71Message;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SequenceMessage&) {}
    virtual void visit(const EmptyBookMessage&) {}
    virtual void visit(const ChannelReset11Message&) {}
    virtual void visit(const SecurityStatus3Message&) {}
    virtual void visit(const SecurityGroupPhase10Message&) {}
    virtual void visit(const DeprecatedSecurityDefinitionMessage&) {}
    virtual void visit(const SecurityDefinitionMessage&) {}
    virtual void visit(const News5Message&) {}
    virtual void visit(const OpeningPrice15Message&) {}
    virtual void visit(const TheoreticalOpeningPrice16Message&) {}
    virtual void visit(const ClosingPrice17Message&) {}
    virtual void visit(const AuctionImbalance19Message&) {}
    virtual void visit(const PriceBand20Message&) {}
    virtual void visit(const QuantityBand21Message&) {}
    virtual void visit(const PriceBand22Message&) {}
    virtual void visit(const HighPrice24Message&) {}
    virtual void visit(const LowPrice25Message&) {}
    virtual void visit(const LastTradePrice27Message&) {}
    virtual void visit(const SettlementPrice28Message&) {}
    virtual void visit(const OpenInterest29Message&) {}
    virtual void visit(const SnapshotFullRefreshHeader30Message&) {}
    virtual void visit(const OrderMbO50Message&) {}
    virtual void visit(const DeleteOrderMbO51Message&) {}
    virtual void visit(const MassDeleteOrdersMbO52Message&) {}
    virtual void visit(const Trade53Message&) {}
    virtual void visit(const ForwardTrade54Message&) {}
    virtual void visit(const ExecutionSummary55Message&) {}
    virtual void visit(const ExecutionStatistics56Message&) {}
    virtual void visit(const TradeBust57Message&) {}
    virtual void visit(const SnapshotFullRefreshOrdersMbO71Message&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
