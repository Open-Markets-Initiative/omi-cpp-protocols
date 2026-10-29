#include "RefMsgType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(RefMsgType value) {
    switch (value) {
        case RefMsgType::Negotiate: return "Negotiate";
        case RefMsgType::NegotiateResponse: return "Negotiate Response";
        case RefMsgType::NegotiateReject: return "Negotiate Reject";
        case RefMsgType::Establish: return "Establish";
        case RefMsgType::EstablishAck: return "Establish Ack";
        case RefMsgType::EstablishReject: return "Establish Reject";
        case RefMsgType::Terminate: return "Terminate";
        case RefMsgType::NotApplied: return "Not Applied";
        case RefMsgType::RetransmitRequest: return "Retransmit Request";
        case RefMsgType::Retransmission: return "Retransmission";
        case RefMsgType::RetransmitReject: return "Retransmit Reject";
        case RefMsgType::Sequence: return "Sequence";
        case RefMsgType::BusinessMessageReject: return "Business Message Reject";
        case RefMsgType::SimpleNewOrder: return "Simple New Order";
        case RefMsgType::SimpleModifyOrder: return "Simple Modify Order";
        case RefMsgType::NewOrderSingle: return "New Order Single";
        case RefMsgType::OrderCancelReplaceRequest: return "Order Cancel Replace Request";
        case RefMsgType::OrderCancelRequest: return "Order Cancel Request";
        case RefMsgType::NewOrderCross: return "New Order Cross";
        case RefMsgType::ExecutionReportNew: return "Execution Report New";
        case RefMsgType::ExecutionReportModify: return "Execution Report Modify";
        case RefMsgType::ExecutionReportCancel: return "Execution Report Cancel";
        case RefMsgType::ExecutionReportTrade: return "Execution Report Trade";
        case RefMsgType::ExecutionReportReject: return "Execution Report Reject";
        case RefMsgType::ExecutionReportForward: return "Execution Report Forward";
        case RefMsgType::SecurityDefinitionRequest: return "Security Definition Request";
        case RefMsgType::SecurityDefinitionResponse: return "Security Definition Response";
        case RefMsgType::OrderMassActionRequest: return "Order Mass Action Request";
        case RefMsgType::OrderMassActionReport: return "Order Mass Action Report";
        case RefMsgType::QuoteRequest: return "Quote Request";
        case RefMsgType::QuoteStatusReport: return "Quote Status Report";
        case RefMsgType::Quote: return "Quote";
        case RefMsgType::QuoteCancel: return "Quote Cancel";
        case RefMsgType::QuoteRequestReject: return "Quote Request Reject";
        case RefMsgType::PositionMaintenanceCancelRequest: return "Position Maintenance Cancel Request";
        case RefMsgType::PositionMaintenanceRequest: return "Position Maintenance Request";
        case RefMsgType::PositionMaintenanceReport: return "Position Maintenance Report";
        case RefMsgType::AllocationInstruction: return "Allocation Instruction";
        case RefMsgType::AllocationReport: return "Allocation Report";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RefMsgType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
