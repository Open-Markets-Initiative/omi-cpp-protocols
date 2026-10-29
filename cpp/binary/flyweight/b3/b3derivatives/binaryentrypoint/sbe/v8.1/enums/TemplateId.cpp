#include "TemplateId.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

std::string_view to_string(TemplateId value) {
    switch (value) {
        case TemplateId::NegotiateMessage: return "Negotiate Message";
        case TemplateId::NegotiateResponseMessage: return "Negotiate Response Message";
        case TemplateId::NegotiateRejectMessage: return "Negotiate Reject Message";
        case TemplateId::EstablishMessage: return "Establish Message";
        case TemplateId::EstablishAckMessage: return "Establish Ack Message";
        case TemplateId::EstablishRejectMessage: return "Establish Reject Message";
        case TemplateId::TerminateMessage: return "Terminate Message";
        case TemplateId::NotAppliedMessage: return "Not Applied Message";
        case TemplateId::SequenceMessage: return "Sequence Message";
        case TemplateId::RetransmitRequestMessage: return "Retransmit Request Message";
        case TemplateId::RetransmissionMessage: return "Retransmission Message";
        case TemplateId::RetransmitRejectMessage: return "Retransmit Reject Message";
        case TemplateId::SimpleNewOrderMessage: return "Simple New Order Message";
        case TemplateId::SimpleModifyOrderMessage: return "Simple Modify Order Message";
        case TemplateId::NewOrderSingleMessage: return "New Order Single Message";
        case TemplateId::OrderCancelReplaceRequestMessage: return "Order Cancel Replace Request Message";
        case TemplateId::OrderCancelRequestMessage: return "Order Cancel Request Message";
        case TemplateId::NewOrderCrossMessage: return "New Order Cross Message";
        case TemplateId::ExecutionReportNewMessage: return "Execution Report New Message";
        case TemplateId::ExecutionReportModifyMessage: return "Execution Report Modify Message";
        case TemplateId::ExecutionReportCancelMessage: return "Execution Report Cancel Message";
        case TemplateId::ExecutionReportTradeMessage: return "Execution Report Trade Message";
        case TemplateId::ExecutionReportRejectMessage: return "Execution Report Reject Message";
        case TemplateId::ExecutionReportForwardMessage: return "Execution Report Forward Message";
        case TemplateId::BusinessMessageRejectMessage: return "Business Message Reject Message";
        case TemplateId::SecurityDefinitionRequestMessage: return "Security Definition Request Message";
        case TemplateId::SecurityDefinitionResponseMessage: return "Security Definition Response Message";
        case TemplateId::QuoteRequestMessage: return "Quote Request Message";
        case TemplateId::QuoteStatusReportMessage: return "Quote Status Report Message";
        case TemplateId::QuoteMessage: return "Quote Message";
        case TemplateId::QuoteCancelMessage: return "Quote Cancel Message";
        case TemplateId::QuoteRequestRejectMessage: return "Quote Request Reject Message";
        case TemplateId::PositionMaintenanceCancelRequestMessage: return "Position Maintenance Cancel Request Message";
        case TemplateId::PositionMaintenanceRequestMessage: return "Position Maintenance Request Message";
        case TemplateId::PositionMaintenanceReportMessage: return "Position Maintenance Report Message";
        case TemplateId::AllocationInstructionMessage: return "Allocation Instruction Message";
        case TemplateId::AllocationReportMessage: return "Allocation Report Message";
        case TemplateId::OrderMassActionRequestMessage: return "Order Mass Action Request Message";
        case TemplateId::OrderMassActionReportMessage: return "Order Mass Action Report Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TemplateId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
