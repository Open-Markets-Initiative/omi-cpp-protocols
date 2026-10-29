#pragma once

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

class NegotiateMessage;
class NegotiateResponseMessage;
class NegotiateRejectMessage;
class EstablishMessage;
class EstablishAckMessage;
class EstablishRejectMessage;
class TerminateMessage;
class NotAppliedMessage;
class SequenceMessage;
class RetransmitRequestMessage;
class RetransmissionMessage;
class RetransmitRejectMessage;
class SimpleNewOrderMessage;
class SimpleModifyOrderMessage;
class NewOrderSingleMessage;
class OrderCancelReplaceRequestMessage;
class OrderCancelRequestMessage;
class NewOrderCrossMessage;
class ExecutionReportNewMessage;
class ExecutionReportModifyMessage;
class ExecutionReportCancelMessage;
class ExecutionReportTradeMessage;
class ExecutionReportRejectMessage;
class ExecutionReportForwardMessage;
class BusinessMessageRejectMessage;
class SecurityDefinitionRequestMessage;
class SecurityDefinitionResponseMessage;
class QuoteRequestMessage;
class QuoteStatusReportMessage;
class QuoteMessage;
class QuoteCancelMessage;
class QuoteRequestRejectMessage;
class PositionMaintenanceCancelRequestMessage;
class PositionMaintenanceRequestMessage;
class PositionMaintenanceReportMessage;
class AllocationInstructionMessage;
class AllocationReportMessage;
class OrderMassActionRequestMessage;
class OrderMassActionReportMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const NegotiateMessage&) {}
    virtual void visit(const NegotiateResponseMessage&) {}
    virtual void visit(const NegotiateRejectMessage&) {}
    virtual void visit(const EstablishMessage&) {}
    virtual void visit(const EstablishAckMessage&) {}
    virtual void visit(const EstablishRejectMessage&) {}
    virtual void visit(const TerminateMessage&) {}
    virtual void visit(const NotAppliedMessage&) {}
    virtual void visit(const SequenceMessage&) {}
    virtual void visit(const RetransmitRequestMessage&) {}
    virtual void visit(const RetransmissionMessage&) {}
    virtual void visit(const RetransmitRejectMessage&) {}
    virtual void visit(const SimpleNewOrderMessage&) {}
    virtual void visit(const SimpleModifyOrderMessage&) {}
    virtual void visit(const NewOrderSingleMessage&) {}
    virtual void visit(const OrderCancelReplaceRequestMessage&) {}
    virtual void visit(const OrderCancelRequestMessage&) {}
    virtual void visit(const NewOrderCrossMessage&) {}
    virtual void visit(const ExecutionReportNewMessage&) {}
    virtual void visit(const ExecutionReportModifyMessage&) {}
    virtual void visit(const ExecutionReportCancelMessage&) {}
    virtual void visit(const ExecutionReportTradeMessage&) {}
    virtual void visit(const ExecutionReportRejectMessage&) {}
    virtual void visit(const ExecutionReportForwardMessage&) {}
    virtual void visit(const BusinessMessageRejectMessage&) {}
    virtual void visit(const SecurityDefinitionRequestMessage&) {}
    virtual void visit(const SecurityDefinitionResponseMessage&) {}
    virtual void visit(const QuoteRequestMessage&) {}
    virtual void visit(const QuoteStatusReportMessage&) {}
    virtual void visit(const QuoteMessage&) {}
    virtual void visit(const QuoteCancelMessage&) {}
    virtual void visit(const QuoteRequestRejectMessage&) {}
    virtual void visit(const PositionMaintenanceCancelRequestMessage&) {}
    virtual void visit(const PositionMaintenanceRequestMessage&) {}
    virtual void visit(const PositionMaintenanceReportMessage&) {}
    virtual void visit(const AllocationInstructionMessage&) {}
    virtual void visit(const AllocationReportMessage&) {}
    virtual void visit(const OrderMassActionRequestMessage&) {}
    virtual void visit(const OrderMassActionReportMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
