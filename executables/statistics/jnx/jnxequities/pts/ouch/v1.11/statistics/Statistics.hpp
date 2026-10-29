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
#include "cpp/binary/modern/jnx/jnxequities/pts/ouch/v1.11/definitions.hpp"

namespace statistics {

// Jnx Ouch C++ statistics
struct Statistics {

    jnx::jnxequities::pts::ouch::v1_11::ClientSoupBinTcpPacketIterator client_soup_bin_tcp_packet;
    jnx::jnxequities::pts::ouch::v1_11::ServerSoupBinTcpPacketIterator server_soup_bin_tcp_packet;
    packet::TcpReassembler client_soup_bin_tcp_packet_reassembler;
    std::unordered_map<packet::TcpFlowKey, std::vector<std::uint8_t>, packet::TcpFlowKey::hash> client_soup_bin_tcp_packet_flows;
    packet::TcpReassembler server_soup_bin_tcp_packet_reassembler;
    std::unordered_map<packet::TcpFlowKey, std::vector<std::uint8_t>, packet::TcpFlowKey::hash> server_soup_bin_tcp_packet_flows;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t debug_packet = 0;
    uint64_t login_request_packet = 0;
    uint64_t unsequenced_data_packet = 0;
    uint64_t enter_order_message = 0;
    uint64_t replace_order_message = 0;
    uint64_t cancel_order_message = 0;
    uint64_t login_accepted_packet = 0;
    uint64_t login_rejected_packet = 0;
    uint64_t sequenced_data_packet = 0;
    uint64_t system_event_message = 0;
    uint64_t order_accepted_message = 0;
    uint64_t order_replaced_message = 0;
    uint64_t order_canceled_message = 0;
    uint64_t order_aiq_canceled_message = 0;
    uint64_t order_executed_message = 0;
    uint64_t order_rejected_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {
        client_soup_bin_tcp_packet_reassembler.on_data = [this](const packet::TcpFlowKey& key, const std::byte* data, std::size_t length) { client_soup_bin_tcp_packet_flow(key, data, length); };
        server_soup_bin_tcp_packet_reassembler.on_data = [this](const packet::TcpFlowKey& key, const std::byte* data, std::size_t length) { server_soup_bin_tcp_packet_flow(key, data, length); };
    }

    // process a frame: every tree carrying its transport reads it
    void udp() {
        const auto& frame = parser.frame();

        if (frame.is_tcp()) {
            client_soup_bin_tcp_packet_reassembler.process(frame);
            server_soup_bin_tcp_packet_reassembler.process(frame);
        }
    }

    // walk the Client Packet tree's reassembled bytes
    void client_soup_bin_tcp_packet_flow(const packet::TcpFlowKey& key, const std::byte* data, std::size_t length) {
        auto& bytes = client_soup_bin_tcp_packet_flows[key];
        bytes.insert(bytes.end(),
                     reinterpret_cast<const std::uint8_t*>(data),
                     reinterpret_cast<const std::uint8_t*>(data) + length);

        const auto* base = reinterpret_cast<const std::byte*>(bytes.data());
        client_soup_bin_tcp_packet.initialize(base, bytes.size());

        std::size_t consumed = 0;

        while (client_soup_bin_tcp_packet.next()) {
            if (client_soup_bin_tcp_packet.current > client_soup_bin_tcp_packet.end) { break; }   // the packet's bytes have not all arrived

            consumed = static_cast<std::size_t>(client_soup_bin_tcp_packet.current - base);
            if (client_soup_bin_tcp_packet.client_packet_type == 'R' || client_soup_bin_tcp_packet.client_packet_type == 'O') {
                ++heartbeats;
                continue;
            }

            process_client_soup_bin_tcp_packet(client_soup_bin_tcp_packet.message, client_soup_bin_tcp_packet.client_packet_type);
        }

        // drop what was read, keeping the packet that is still arriving
        if (consumed > 0) {
            bytes.erase(bytes.begin(), bytes.begin() + static_cast<std::ptrdiff_t>(consumed));
        }
    }

    // walk the Server Packet tree's reassembled bytes
    void server_soup_bin_tcp_packet_flow(const packet::TcpFlowKey& key, const std::byte* data, std::size_t length) {
        auto& bytes = server_soup_bin_tcp_packet_flows[key];
        bytes.insert(bytes.end(),
                     reinterpret_cast<const std::uint8_t*>(data),
                     reinterpret_cast<const std::uint8_t*>(data) + length);

        const auto* base = reinterpret_cast<const std::byte*>(bytes.data());
        server_soup_bin_tcp_packet.initialize(base, bytes.size());

        std::size_t consumed = 0;

        while (server_soup_bin_tcp_packet.next()) {
            if (server_soup_bin_tcp_packet.current > server_soup_bin_tcp_packet.end) { break; }   // the packet's bytes have not all arrived

            consumed = static_cast<std::size_t>(server_soup_bin_tcp_packet.current - base);
            if (server_soup_bin_tcp_packet.server_packet_type == 'H' || server_soup_bin_tcp_packet.server_packet_type == 'Z') {
                ++heartbeats;
                continue;
            }

            process_server_soup_bin_tcp_packet(server_soup_bin_tcp_packet.message, server_soup_bin_tcp_packet.server_packet_type);
        }

        // drop what was read, keeping the packet that is still arriving
        if (consumed > 0) {
            bytes.erase(bytes.begin(), bytes.begin() + static_cast<std::ptrdiff_t>(consumed));
        }
    }

    // count a message of the Client Packet tree
    void process_client_soup_bin_tcp_packet(const std::byte* pointer, const char client_packet_type) {
        switch (client_packet_type) {
            case '+':
                ++total_messages;
                ++debug_packet;
                break;
            case 'L':
                ++total_messages;
                ++login_request_packet;
                break;
            case 'U':
                ++total_messages;
                ++unsequenced_data_packet;
                {
                    const auto* sub_header = jnx::jnxequities::pts::ouch::v1_11::UnsequencedDataPacket::parse(pointer);
                    const char unsequenced_message_type = sub_header->unsequenced_message_type.get();
                    switch (unsequenced_message_type) {
                        case 'O':
                            ++enter_order_message;
                            break;
                        case 'U':
                            ++replace_order_message;
                            break;
                        case 'X':
                            ++cancel_order_message;
                            break;
                        default:
                            ++unknown_messages;
                            break;
                    }
                }
                break;

            default:
                break;   // another tree's client_packet_type
                break;
        }
    }

    // count a message of the Server Packet tree
    void process_server_soup_bin_tcp_packet(const std::byte* pointer, const char server_packet_type) {
        switch (server_packet_type) {
            case '+':
                ++total_messages;
                ++debug_packet;
                break;
            case 'A':
                ++total_messages;
                ++login_accepted_packet;
                break;
            case 'J':
                ++total_messages;
                ++login_rejected_packet;
                break;
            case 'S':
                ++total_messages;
                ++sequenced_data_packet;
                {
                    const auto* sub_header = jnx::jnxequities::pts::ouch::v1_11::SequencedDataPacket::parse(pointer);
                    const char sequenced_message_type = sub_header->sequenced_message_type.get();
                    switch (sequenced_message_type) {
                        case 'S':
                            ++system_event_message;
                            break;
                        case 'A':
                            ++order_accepted_message;
                            break;
                        case 'U':
                            ++order_replaced_message;
                            break;
                        case 'C':
                            ++order_canceled_message;
                            break;
                        case 'D':
                            ++order_aiq_canceled_message;
                            break;
                        case 'E':
                            ++order_executed_message;
                            break;
                        case 'J':
                            ++order_rejected_message;
                            break;
                        default:
                            ++unknown_messages;
                            break;
                    }
                }
                break;

            default:
                break;   // another tree's server_packet_type
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
        std::cout << "  DebugPacket (+)              " << debug_packet << std::endl;
        std::cout << "  LoginRequestPacket (L)       " << login_request_packet << std::endl;
        std::cout << "  UnsequencedDataPacket (U)    " << unsequenced_data_packet << std::endl;
        std::cout << "  EnterOrderMessage (O)        " << enter_order_message << std::endl;
        std::cout << "  ReplaceOrderMessage (U)      " << replace_order_message << std::endl;
        std::cout << "  CancelOrderMessage (X)       " << cancel_order_message << std::endl;
        std::cout << "  LoginAcceptedPacket (A)      " << login_accepted_packet << std::endl;
        std::cout << "  LoginRejectedPacket (J)      " << login_rejected_packet << std::endl;
        std::cout << "  SequencedDataPacket (S)      " << sequenced_data_packet << std::endl;
        std::cout << "  SystemEventMessage (S)       " << system_event_message << std::endl;
        std::cout << "  OrderAcceptedMessage (A)     " << order_accepted_message << std::endl;
        std::cout << "  OrderReplacedMessage (U)     " << order_replaced_message << std::endl;
        std::cout << "  OrderCanceledMessage (C)     " << order_canceled_message << std::endl;
        std::cout << "  OrderAiqCanceledMessage (D)  " << order_aiq_canceled_message << std::endl;
        std::cout << "  OrderExecutedMessage (E)     " << order_executed_message << std::endl;
        std::cout << "  OrderRejectedMessage (J)     " << order_rejected_message << std::endl;
    }
};
}
