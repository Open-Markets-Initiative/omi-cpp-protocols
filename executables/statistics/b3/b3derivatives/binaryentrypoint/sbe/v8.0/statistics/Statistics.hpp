#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <unordered_map>
#include <vector>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "../pcap/TcpReassembler.hpp"
#include "cpp/binary/modern/b3/b3derivatives/binaryentrypoint/sbe/v8.0/definitions.hpp"

namespace statistics {

// B3 Sbe C++ statistics
struct Statistics {

    b3::b3derivatives::binaryentrypoint::sbe::v8_0::SimpleOpenFrameIterator simple_open_frame;
    packet::TcpReassembler simple_open_frame_reassembler;
    std::unordered_map<packet::TcpFlowKey, std::vector<std::uint8_t>, packet::TcpFlowKey::hash> simple_open_frame_flows;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t negotiate_message = 0;
    uint64_t negotiate_response_message = 0;
    uint64_t negotiate_reject_message = 0;
    uint64_t establish_message = 0;
    uint64_t establish_ack_message = 0;
    uint64_t establish_reject_message = 0;
    uint64_t terminate_message = 0;
    uint64_t not_applied_message = 0;
    uint64_t sequence_message = 0;
    uint64_t retransmit_request_message = 0;
    uint64_t retransmission_message = 0;
    uint64_t retransmit_reject_message = 0;
    uint64_t simple_new_order_message = 0;
    uint64_t simple_modify_order_message = 0;
    uint64_t new_order_single_message = 0;
    uint64_t order_cancel_replace_request_message = 0;
    uint64_t order_cancel_request_message = 0;
    uint64_t new_order_cross_message = 0;
    uint64_t execution_report_new_message = 0;
    uint64_t execution_report_modify_message = 0;
    uint64_t execution_report_cancel_message = 0;
    uint64_t execution_report_trade_message = 0;
    uint64_t execution_report_reject_message = 0;
    uint64_t execution_report_forward_message = 0;
    uint64_t business_message_reject_message = 0;
    uint64_t security_definition_request_message = 0;
    uint64_t security_definition_response_message = 0;
    uint64_t quote_request_message = 0;
    uint64_t quote_status_report_message = 0;
    uint64_t quote_message = 0;
    uint64_t quote_cancel_message = 0;
    uint64_t quote_request_reject_message = 0;
    uint64_t position_maintenance_cancel_request_message = 0;
    uint64_t position_maintenance_request_message = 0;
    uint64_t position_maintenance_report_message = 0;
    uint64_t allocation_instruction_message = 0;
    uint64_t allocation_report_message = 0;
    uint64_t order_mass_action_request_message = 0;
    uint64_t order_mass_action_report_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {
        simple_open_frame_reassembler.on_data = [this](const packet::TcpFlowKey& key, const std::byte* data, std::size_t length) { simple_open_frame_flow(key, data, length); };
    }

    // process a frame: every tree carrying its transport reads it
    void udp() {
        const auto& frame = parser.frame();

        if (frame.is_tcp()) {
            simple_open_frame_reassembler.process(frame);
        }
    }

    // walk the Packet tree's reassembled bytes
    void simple_open_frame_flow(const packet::TcpFlowKey& key, const std::byte* data, std::size_t length) {
        auto& bytes = simple_open_frame_flows[key];
        bytes.insert(bytes.end(),
                     reinterpret_cast<const std::uint8_t*>(data),
                     reinterpret_cast<const std::uint8_t*>(data) + length);

        const auto* base = reinterpret_cast<const std::byte*>(bytes.data());
        simple_open_frame.initialize(base, bytes.size());

        std::size_t consumed = 0;

        while (simple_open_frame.next()) {
            if (simple_open_frame.current > simple_open_frame.end) { break; }   // the packet's bytes have not all arrived

            consumed = static_cast<std::size_t>(simple_open_frame.current - base);
            process_simple_open_frame(simple_open_frame.message, simple_open_frame.template_id);
        }

        // drop what was read, keeping the packet that is still arriving
        if (consumed > 0) {
            bytes.erase(bytes.begin(), bytes.begin() + static_cast<std::ptrdiff_t>(consumed));
        }
    }

    // count a message of the Packet tree
    void process_simple_open_frame(const std::byte*, const std::uint16_t template_id) {
        switch (template_id) {
            case 1:
                ++total_messages;
                ++negotiate_message;
                break;
            case 2:
                ++total_messages;
                ++negotiate_response_message;
                break;
            case 3:
                ++total_messages;
                ++negotiate_reject_message;
                break;
            case 4:
                ++total_messages;
                ++establish_message;
                break;
            case 5:
                ++total_messages;
                ++establish_ack_message;
                break;
            case 6:
                ++total_messages;
                ++establish_reject_message;
                break;
            case 7:
                ++total_messages;
                ++terminate_message;
                break;
            case 8:
                ++total_messages;
                ++not_applied_message;
                break;
            case 9:
                ++total_messages;
                ++sequence_message;
                break;
            case 12:
                ++total_messages;
                ++retransmit_request_message;
                break;
            case 13:
                ++total_messages;
                ++retransmission_message;
                break;
            case 14:
                ++total_messages;
                ++retransmit_reject_message;
                break;
            case 100:
                ++total_messages;
                ++simple_new_order_message;
                break;
            case 101:
                ++total_messages;
                ++simple_modify_order_message;
                break;
            case 102:
                ++total_messages;
                ++new_order_single_message;
                break;
            case 104:
                ++total_messages;
                ++order_cancel_replace_request_message;
                break;
            case 105:
                ++total_messages;
                ++order_cancel_request_message;
                break;
            case 106:
                ++total_messages;
                ++new_order_cross_message;
                break;
            case 200:
                ++total_messages;
                ++execution_report_new_message;
                break;
            case 201:
                ++total_messages;
                ++execution_report_modify_message;
                break;
            case 202:
                ++total_messages;
                ++execution_report_cancel_message;
                break;
            case 203:
                ++total_messages;
                ++execution_report_trade_message;
                break;
            case 204:
                ++total_messages;
                ++execution_report_reject_message;
                break;
            case 205:
                ++total_messages;
                ++execution_report_forward_message;
                break;
            case 206:
                ++total_messages;
                ++business_message_reject_message;
                break;
            case 300:
                ++total_messages;
                ++security_definition_request_message;
                break;
            case 301:
                ++total_messages;
                ++security_definition_response_message;
                break;
            case 401:
                ++total_messages;
                ++quote_request_message;
                break;
            case 402:
                ++total_messages;
                ++quote_status_report_message;
                break;
            case 403:
                ++total_messages;
                ++quote_message;
                break;
            case 404:
                ++total_messages;
                ++quote_cancel_message;
                break;
            case 405:
                ++total_messages;
                ++quote_request_reject_message;
                break;
            case 501:
                ++total_messages;
                ++position_maintenance_cancel_request_message;
                break;
            case 502:
                ++total_messages;
                ++position_maintenance_request_message;
                break;
            case 503:
                ++total_messages;
                ++position_maintenance_report_message;
                break;
            case 601:
                ++total_messages;
                ++allocation_instruction_message;
                break;
            case 602:
                ++total_messages;
                ++allocation_report_message;
                break;
            case 701:
                ++total_messages;
                ++order_mass_action_request_message;
                break;
            case 702:
                ++total_messages;
                ++order_mass_action_report_message;
                break;

            default:
                ++total_messages;
                ++unknown_messages;
                if (options.verbose) {
                    std::cerr << "Unknown template_id: " << static_cast<int>(template_id) << std::endl;
                }
                break;
        }
    }

    // report statistics
    void report() {
        std::cout << std::endl;
        std::cout << "Statistics Report" << std::endl;
        std::cout << "=================" << std::endl;
        std::cout << "Total packets:   " << total_packets << std::endl;
        std::cout << "Unknown packets: " << unknown_packets << std::endl;
        std::cout << "Total messages:  " << total_messages << std::endl;
        std::cout << "Unknown types:   " << unknown_messages << std::endl;
        std::cout << "Heartbeats:      " << heartbeats << std::endl;

        std::cout << std::endl;
        std::cout << "Message Counts:" << std::endl;
        std::cout << "--------------" << std::endl;
        std::cout << "  NegotiateMessage (1)                           " << negotiate_message << std::endl;
        std::cout << "  NegotiateResponseMessage (2)                   " << negotiate_response_message << std::endl;
        std::cout << "  NegotiateRejectMessage (3)                     " << negotiate_reject_message << std::endl;
        std::cout << "  EstablishMessage (4)                           " << establish_message << std::endl;
        std::cout << "  EstablishAckMessage (5)                        " << establish_ack_message << std::endl;
        std::cout << "  EstablishRejectMessage (6)                     " << establish_reject_message << std::endl;
        std::cout << "  TerminateMessage (7)                           " << terminate_message << std::endl;
        std::cout << "  NotAppliedMessage (8)                          " << not_applied_message << std::endl;
        std::cout << "  SequenceMessage (9)                            " << sequence_message << std::endl;
        std::cout << "  RetransmitRequestMessage (12)                  " << retransmit_request_message << std::endl;
        std::cout << "  RetransmissionMessage (13)                     " << retransmission_message << std::endl;
        std::cout << "  RetransmitRejectMessage (14)                   " << retransmit_reject_message << std::endl;
        std::cout << "  SimpleNewOrderMessage (100)                    " << simple_new_order_message << std::endl;
        std::cout << "  SimpleModifyOrderMessage (101)                 " << simple_modify_order_message << std::endl;
        std::cout << "  NewOrderSingleMessage (102)                    " << new_order_single_message << std::endl;
        std::cout << "  OrderCancelReplaceRequestMessage (104)         " << order_cancel_replace_request_message << std::endl;
        std::cout << "  OrderCancelRequestMessage (105)                " << order_cancel_request_message << std::endl;
        std::cout << "  NewOrderCrossMessage (106)                     " << new_order_cross_message << std::endl;
        std::cout << "  ExecutionReportNewMessage (200)                " << execution_report_new_message << std::endl;
        std::cout << "  ExecutionReportModifyMessage (201)             " << execution_report_modify_message << std::endl;
        std::cout << "  ExecutionReportCancelMessage (202)             " << execution_report_cancel_message << std::endl;
        std::cout << "  ExecutionReportTradeMessage (203)              " << execution_report_trade_message << std::endl;
        std::cout << "  ExecutionReportRejectMessage (204)             " << execution_report_reject_message << std::endl;
        std::cout << "  ExecutionReportForwardMessage (205)            " << execution_report_forward_message << std::endl;
        std::cout << "  BusinessMessageRejectMessage (206)             " << business_message_reject_message << std::endl;
        std::cout << "  SecurityDefinitionRequestMessage (300)         " << security_definition_request_message << std::endl;
        std::cout << "  SecurityDefinitionResponseMessage (301)        " << security_definition_response_message << std::endl;
        std::cout << "  QuoteRequestMessage (401)                      " << quote_request_message << std::endl;
        std::cout << "  QuoteStatusReportMessage (402)                 " << quote_status_report_message << std::endl;
        std::cout << "  QuoteMessage (403)                             " << quote_message << std::endl;
        std::cout << "  QuoteCancelMessage (404)                       " << quote_cancel_message << std::endl;
        std::cout << "  QuoteRequestRejectMessage (405)                " << quote_request_reject_message << std::endl;
        std::cout << "  PositionMaintenanceCancelRequestMessage (501)  " << position_maintenance_cancel_request_message << std::endl;
        std::cout << "  PositionMaintenanceRequestMessage (502)        " << position_maintenance_request_message << std::endl;
        std::cout << "  PositionMaintenanceReportMessage (503)         " << position_maintenance_report_message << std::endl;
        std::cout << "  AllocationInstructionMessage (601)             " << allocation_instruction_message << std::endl;
        std::cout << "  AllocationReportMessage (602)                  " << allocation_report_message << std::endl;
        std::cout << "  OrderMassActionRequestMessage (701)            " << order_mass_action_request_message << std::endl;
        std::cout << "  OrderMassActionReportMessage (702)             " << order_mass_action_report_message << std::endl;
    }
};
}
