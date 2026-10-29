#include "Factory.hpp"

#include "definitions.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case NegotiateMessage::message_type: return std::make_unique<NegotiateMessage>();
        case NegotiateResponseMessage::message_type: return std::make_unique<NegotiateResponseMessage>();
        case NegotiateRejectMessage::message_type: return std::make_unique<NegotiateRejectMessage>();
        case EstablishMessage::message_type: return std::make_unique<EstablishMessage>();
        case EstablishAckMessage::message_type: return std::make_unique<EstablishAckMessage>();
        case EstablishRejectMessage::message_type: return std::make_unique<EstablishRejectMessage>();
        case TerminateMessage::message_type: return std::make_unique<TerminateMessage>();
        case NotAppliedMessage::message_type: return std::make_unique<NotAppliedMessage>();
        case SequenceMessage::message_type: return std::make_unique<SequenceMessage>();
        case RetransmitRequestMessage::message_type: return std::make_unique<RetransmitRequestMessage>();
        case RetransmissionMessage::message_type: return std::make_unique<RetransmissionMessage>();
        case RetransmitRejectMessage::message_type: return std::make_unique<RetransmitRejectMessage>();
        case SimpleNewOrderMessage::message_type: return std::make_unique<SimpleNewOrderMessage>();
        case SimpleModifyOrderMessage::message_type: return std::make_unique<SimpleModifyOrderMessage>();
        case NewOrderSingleMessage::message_type: return std::make_unique<NewOrderSingleMessage>();
        case OrderCancelReplaceRequestMessage::message_type: return std::make_unique<OrderCancelReplaceRequestMessage>();
        case OrderCancelRequestMessage::message_type: return std::make_unique<OrderCancelRequestMessage>();
        case NewOrderCrossMessage::message_type: return std::make_unique<NewOrderCrossMessage>();
        case ExecutionReportNewMessage::message_type: return std::make_unique<ExecutionReportNewMessage>();
        case ExecutionReportModifyMessage::message_type: return std::make_unique<ExecutionReportModifyMessage>();
        case ExecutionReportCancelMessage::message_type: return std::make_unique<ExecutionReportCancelMessage>();
        case ExecutionReportTradeMessage::message_type: return std::make_unique<ExecutionReportTradeMessage>();
        case ExecutionReportRejectMessage::message_type: return std::make_unique<ExecutionReportRejectMessage>();
        case ExecutionReportForwardMessage::message_type: return std::make_unique<ExecutionReportForwardMessage>();
        case BusinessMessageRejectMessage::message_type: return std::make_unique<BusinessMessageRejectMessage>();
        case SecurityDefinitionRequestMessage::message_type: return std::make_unique<SecurityDefinitionRequestMessage>();
        case SecurityDefinitionResponseMessage::message_type: return std::make_unique<SecurityDefinitionResponseMessage>();
        case QuoteRequestMessage::message_type: return std::make_unique<QuoteRequestMessage>();
        case QuoteStatusReportMessage::message_type: return std::make_unique<QuoteStatusReportMessage>();
        case QuoteMessage::message_type: return std::make_unique<QuoteMessage>();
        case QuoteCancelMessage::message_type: return std::make_unique<QuoteCancelMessage>();
        case QuoteRequestRejectMessage::message_type: return std::make_unique<QuoteRequestRejectMessage>();
        case PositionMaintenanceCancelRequestMessage::message_type: return std::make_unique<PositionMaintenanceCancelRequestMessage>();
        case PositionMaintenanceRequestMessage::message_type: return std::make_unique<PositionMaintenanceRequestMessage>();
        case PositionMaintenanceReportMessage::message_type: return std::make_unique<PositionMaintenanceReportMessage>();
        case AllocationInstructionMessage::message_type: return std::make_unique<AllocationInstructionMessage>();
        case AllocationReportMessage::message_type: return std::make_unique<AllocationReportMessage>();
        case OrderMassActionRequestMessage::message_type: return std::make_unique<OrderMassActionRequestMessage>();
        case OrderMassActionReportMessage::message_type: return std::make_unique<OrderMassActionReportMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
