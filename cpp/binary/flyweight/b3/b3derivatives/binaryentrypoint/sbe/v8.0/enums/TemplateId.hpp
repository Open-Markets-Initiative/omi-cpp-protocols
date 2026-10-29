#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// Template ID used to encode the message
enum class TemplateId : std::uint16_t {
    NegotiateMessage = 1,                          // Negotiate Message
    NegotiateResponseMessage = 2,                  // Negotiate Response Message
    NegotiateRejectMessage = 3,                    // Negotiate Reject Message
    EstablishMessage = 4,                          // Establish Message
    EstablishAckMessage = 5,                       // Establish Ack Message
    EstablishRejectMessage = 6,                    // Establish Reject Message
    TerminateMessage = 7,                          // Terminate Message
    NotAppliedMessage = 8,                         // Not Applied Message
    SequenceMessage = 9,                           // Sequence Message
    RetransmitRequestMessage = 12,                 // Retransmit Request Message
    RetransmissionMessage = 13,                    // Retransmission Message
    RetransmitRejectMessage = 14,                  // Retransmit Reject Message
    SimpleNewOrderMessage = 100,                   // Simple New Order Message
    SimpleModifyOrderMessage = 101,                // Simple Modify Order Message
    NewOrderSingleMessage = 102,                   // New Order Single Message
    OrderCancelReplaceRequestMessage = 104,        // Order Cancel Replace Request Message
    OrderCancelRequestMessage = 105,               // Order Cancel Request Message
    NewOrderCrossMessage = 106,                    // New Order Cross Message
    ExecutionReportNewMessage = 200,               // Execution Report New Message
    ExecutionReportModifyMessage = 201,            // Execution Report Modify Message
    ExecutionReportCancelMessage = 202,            // Execution Report Cancel Message
    ExecutionReportTradeMessage = 203,             // Execution Report Trade Message
    ExecutionReportRejectMessage = 204,            // Execution Report Reject Message
    ExecutionReportForwardMessage = 205,           // Execution Report Forward Message
    BusinessMessageRejectMessage = 206,            // Business Message Reject Message
    SecurityDefinitionRequestMessage = 300,        // Security Definition Request Message
    SecurityDefinitionResponseMessage = 301,       // Security Definition Response Message
    QuoteRequestMessage = 401,                     // Quote Request Message
    QuoteStatusReportMessage = 402,                // Quote Status Report Message
    QuoteMessage = 403,                            // Quote Message
    QuoteCancelMessage = 404,                      // Quote Cancel Message
    QuoteRequestRejectMessage = 405,               // Quote Request Reject Message
    PositionMaintenanceCancelRequestMessage = 501, // Position Maintenance Cancel Request Message
    PositionMaintenanceRequestMessage = 502,       // Position Maintenance Request Message
    PositionMaintenanceReportMessage = 503,        // Position Maintenance Report Message
    AllocationInstructionMessage = 601,            // Allocation Instruction Message
    AllocationReportMessage = 602,                 // Allocation Report Message
    OrderMassActionRequestMessage = 701,           // Order Mass Action Request Message
    OrderMassActionReportMessage = 702,            // Order Mass Action Report Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TemplateId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TemplateId value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
