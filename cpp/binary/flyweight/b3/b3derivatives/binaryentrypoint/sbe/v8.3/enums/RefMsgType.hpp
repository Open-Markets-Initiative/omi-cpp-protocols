#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// refMsgType
enum class RefMsgType : std::uint8_t {
    Negotiate = 0,                         // Negotiate
    NegotiateResponse = 1,                 // Negotiate Response
    NegotiateReject = 2,                   // Negotiate Reject
    Establish = 3,                         // Establish
    EstablishAck = 4,                      // Establish Ack
    EstablishReject = 5,                   // Establish Reject
    Terminate = 6,                         // Terminate
    NotApplied = 9,                        // Not Applied
    RetransmitRequest = 10,                // Retransmit Request
    Retransmission = 11,                   // Retransmission
    RetransmitReject = 12,                 // Retransmit Reject
    Sequence = 13,                         // Sequence
    BusinessMessageReject = 14,            // Business Message Reject
    SimpleNewOrder = 15,                   // Simple New Order
    SimpleModifyOrder = 16,                // Simple Modify Order
    NewOrderSingle = 17,                   // New Order Single
    OrderCancelReplaceRequest = 18,        // Order Cancel Replace Request
    OrderCancelRequest = 19,               // Order Cancel Request
    NewOrderCross = 20,                    // New Order Cross
    ExecutionReportNew = 21,               // Execution Report New
    ExecutionReportModify = 22,            // Execution Report Modify
    ExecutionReportCancel = 23,            // Execution Report Cancel
    ExecutionReportTrade = 24,             // Execution Report Trade
    ExecutionReportReject = 25,            // Execution Report Reject
    ExecutionReportForward = 26,           // Execution Report Forward
    SecurityDefinitionRequest = 27,        // Security Definition Request
    SecurityDefinitionResponse = 28,       // Security Definition Response
    OrderMassActionRequest = 29,           // Order Mass Action Request
    OrderMassActionReport = 30,            // Order Mass Action Report
    QuoteRequest = 31,                     // Quote Request
    QuoteStatusReport = 32,                // Quote Status Report
    Quote = 33,                            // Quote
    QuoteCancel = 34,                      // Quote Cancel
    QuoteRequestReject = 35,               // Quote Request Reject
    PositionMaintenanceCancelRequest = 36, // Position Maintenance Cancel Request
    PositionMaintenanceRequest = 37,       // Position Maintenance Request
    PositionMaintenanceReport = 38,        // Position Maintenance Report
    AllocationInstruction = 39,            // Allocation Instruction
    AllocationReport = 40,                 // Allocation Report
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RefMsgType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RefMsgType value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
