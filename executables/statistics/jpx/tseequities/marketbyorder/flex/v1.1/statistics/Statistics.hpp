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
#include "cpp/modern/jpx/tseequities/marketbyorder/flex/v1.1/definitions.hpp"

namespace statistics {

// Jpx Flex C++ statistics
struct Statistics {

    jpx::tseequities::marketbyorder::flex::v1_1::MessageIterator message;
    jpx::tseequities::marketbyorder::flex::v1_1::TcpPacketIterator tcp_packet;
    packet::TcpReassembler tcp_packet_reassembler;
    std::unordered_map<packet::TcpFlowKey, std::vector<std::uint8_t>, packet::TcpFlowKey::hash> tcp_packet_flows;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t seconds_timestamp_message = 0;
    uint64_t trading_status_message = 0;
    uint64_t execution_summary_message = 0;
    uint64_t add_order_message = 0;
    uint64_t order_executed_message = 0;
    uint64_t order_executed_with_price_message = 0;
    uint64_t order_delete_message = 0;
    uint64_t reset_message = 0;
    uint64_t communication_control_message = 0;
    uint64_t login_request_retransmission_message = 0;
    uint64_t login_request_snapshot_message = 0;
    uint64_t login_result_accepted_message = 0;
    uint64_t login_result_rejected_message = 0;
    uint64_t message_response_message = 0;
    uint64_t end_of_message_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {
        tcp_packet_reassembler.on_data = [this](const packet::TcpFlowKey& key, const std::byte* data, std::size_t length) { tcp_packet_flow(key, data, length); };
    }

    // process a frame: every tree carrying its transport reads it
    void udp() {
        const auto& frame = parser.frame();

        if (frame.is_udp()) {
            walk_message(frame);
        }

        if (frame.is_tcp()) {
            tcp_packet_reassembler.process(frame);
        }
    }

    // walk the Udp Packet tree's datagrams
    void walk_message(const packet::Frame& frame) {
        message.initialize(frame.payload, frame.payload_len);

        while (message.next()) {
            process_message(message.message, message.message_type);
        }
    }

    // walk the Tcp Packet tree's reassembled bytes
    void tcp_packet_flow(const packet::TcpFlowKey& key, const std::byte* data, std::size_t length) {
        auto& bytes = tcp_packet_flows[key];
        bytes.insert(bytes.end(),
                     reinterpret_cast<const std::uint8_t*>(data),
                     reinterpret_cast<const std::uint8_t*>(data) + length);

        const auto* base = reinterpret_cast<const std::byte*>(bytes.data());
        tcp_packet.initialize(base, bytes.size());

        std::size_t consumed = 0;

        while (tcp_packet.next()) {
            if (tcp_packet.current > tcp_packet.end) { break; }   // the packet's bytes have not all arrived

            consumed = static_cast<std::size_t>(tcp_packet.current - base);
            process_tcp_packet(tcp_packet.message, tcp_packet.packet_type);
        }

        // drop what was read, keeping the packet that is still arriving
        if (consumed > 0) {
            bytes.erase(bytes.begin(), bytes.begin() + static_cast<std::ptrdiff_t>(consumed));
        }
    }

    // count a message of the Udp Packet tree
    void process_message(const std::byte*, const char message_type) {
        switch (message_type) {
            case 'T':
                ++total_messages;
                ++seconds_timestamp_message;
                break;
            case 'O':
                ++total_messages;
                ++trading_status_message;
                break;
            case 'K':
                ++total_messages;
                ++execution_summary_message;
                break;
            case 'A':
                ++total_messages;
                ++add_order_message;
                break;
            case 'E':
                ++total_messages;
                ++order_executed_message;
                break;
            case 'C':
                ++total_messages;
                ++order_executed_with_price_message;
                break;
            case 'D':
                ++total_messages;
                ++order_delete_message;
                break;
            case 'R':
                ++total_messages;
                ++reset_message;
                break;
            case 'L':
                ++total_messages;
                ++communication_control_message;
                break;

            default:
                ++total_messages;
                ++unknown_messages;
                if (options.verbose) {
                    std::cerr << "Unknown message_type: " << static_cast<int>(message_type) << std::endl;
                }
                break;
        }
    }

    // count a message of the Tcp Packet tree
    void process_tcp_packet(const std::byte*, const char packet_type) {
        switch (packet_type) {
            case 'R':
                ++total_messages;
                ++login_request_retransmission_message;
                break;
            case 'L':
                ++total_messages;
                ++login_request_snapshot_message;
                break;
            case 'A':
                ++total_messages;
                ++login_result_accepted_message;
                break;
            case 'J':
                ++total_messages;
                ++login_result_rejected_message;
                break;
            case 'S':
                ++total_messages;
                ++message_response_message;
                break;
            case 'G':
                ++total_messages;
                ++end_of_message_message;
                break;

            default:
                ++total_messages;
                ++unknown_messages;
                if (options.verbose) {
                    std::cerr << "Unknown packet_type: " << static_cast<int>(packet_type) << std::endl;
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
        std::cout << "  SecondsTimestampMessage (T)            " << seconds_timestamp_message << std::endl;
        std::cout << "  TradingStatusMessage (O)               " << trading_status_message << std::endl;
        std::cout << "  ExecutionSummaryMessage (K)            " << execution_summary_message << std::endl;
        std::cout << "  AddOrderMessage (A)                    " << add_order_message << std::endl;
        std::cout << "  OrderExecutedMessage (E)               " << order_executed_message << std::endl;
        std::cout << "  OrderExecutedWithPriceMessage (C)      " << order_executed_with_price_message << std::endl;
        std::cout << "  OrderDeleteMessage (D)                 " << order_delete_message << std::endl;
        std::cout << "  ResetMessage (R)                       " << reset_message << std::endl;
        std::cout << "  CommunicationControlMessage (L)        " << communication_control_message << std::endl;
        std::cout << "  LoginRequestRetransmissionMessage (R)  " << login_request_retransmission_message << std::endl;
        std::cout << "  LoginRequestSnapshotMessage (L)        " << login_request_snapshot_message << std::endl;
        std::cout << "  LoginResultAcceptedMessage (A)         " << login_result_accepted_message << std::endl;
        std::cout << "  LoginResultRejectedMessage (J)         " << login_result_rejected_message << std::endl;
        std::cout << "  MessageResponseMessage (S)             " << message_response_message << std::endl;
        std::cout << "  EndOfMessageMessage (G)                " << end_of_message_message << std::endl;
    }
};
}
