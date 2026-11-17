// Databento.MarketData.Normalized.Dbn.v2: Visitor.hpp
#pragma once

namespace databento::marketdata::normalized::dbn::v2 {

class TradeMsg;
class Mbp1Msg;
class Mbp10Msg;
class OhlcvMsg;
class StatusMsg;
class InstrumentDefMsg;
class ImbalanceMsg;
class ErrorMsg;
class SymbolMappingMsg;
class SystemMsg;
class StatMsg;
class MboMsg;
class Cmbp1Msg;
class CbboMsg;
class BboMsg;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const TradeMsg&) {}
    virtual void visit(const Mbp1Msg&) {}
    virtual void visit(const Mbp10Msg&) {}
    virtual void visit(const OhlcvMsg&) {}
    virtual void visit(const StatusMsg&) {}
    virtual void visit(const InstrumentDefMsg&) {}
    virtual void visit(const ImbalanceMsg&) {}
    virtual void visit(const ErrorMsg&) {}
    virtual void visit(const SymbolMappingMsg&) {}
    virtual void visit(const SystemMsg&) {}
    virtual void visit(const StatMsg&) {}
    virtual void visit(const MboMsg&) {}
    virtual void visit(const Cmbp1Msg&) {}
    virtual void visit(const CbboMsg&) {}
    virtual void visit(const BboMsg&) {}
    virtual void visit(const UnknownMessage&) {}
};

class RecordBodyTradeMsg;
class RecordBodyMbp1Msg;
class RecordBodyMbp10Msg;
class RecordBodyOhlcvMsg;
class RecordBodyStatusMsg;
class RecordBodyInstrumentDefMsg;
class RecordBodyImbalanceMsg;
class RecordBodyErrorMsg;
class RecordBodySymbolMappingMsg;
class RecordBodySystemMsg;
class RecordBodyStatMsg;
class RecordBodyMboMsg;
class RecordBodyCmbp1Msg;
class RecordBodyCbboMsg;
class RecordBodyBboMsg;
class UnknownGatewayMessage;

// What the messages of the Record Body dispatch are handed to,
// reached through the record_body a Record holds.
class GatewayMessageVisitor {
  public:
    virtual ~GatewayMessageVisitor() = default;

    virtual void visit(const RecordBodyTradeMsg&) {}
    virtual void visit(const RecordBodyMbp1Msg&) {}
    virtual void visit(const RecordBodyMbp10Msg&) {}
    virtual void visit(const RecordBodyOhlcvMsg&) {}
    virtual void visit(const RecordBodyStatusMsg&) {}
    virtual void visit(const RecordBodyInstrumentDefMsg&) {}
    virtual void visit(const RecordBodyImbalanceMsg&) {}
    virtual void visit(const RecordBodyErrorMsg&) {}
    virtual void visit(const RecordBodySymbolMappingMsg&) {}
    virtual void visit(const RecordBodySystemMsg&) {}
    virtual void visit(const RecordBodyStatMsg&) {}
    virtual void visit(const RecordBodyMboMsg&) {}
    virtual void visit(const RecordBodyCmbp1Msg&) {}
    virtual void visit(const RecordBodyCbboMsg&) {}
    virtual void visit(const RecordBodyBboMsg&) {}
    virtual void visit(const UnknownGatewayMessage&) {}
};

} // namespace databento::marketdata::normalized::dbn::v2
