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
#include "cpp/binary/modern/miax/pearlequities/depthofmarket/mach/v1.3.d/definitions.hpp"

namespace statistics {

// Miax Mach C++ statistics
struct Statistics {

    miax::pearlequities::depthofmarket::mach::v1_3_d::MachMessageIterator mach_message;
    miax::pearlequities::depthofmarket::mach::v1_3_d::EsesmTcpPacketIterator esesm_tcp_packet;
    packet::TcpReassembler esesm_tcp_packet_reassembler;
    std::unordered_map<packet::TcpFlowKey, std::vector<std::uint8_t>, packet::TcpFlowKey::hash> esesm_tcp_packet_flows;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t application_message = 0;
    uint64_t system_time_message = 0;
    uint64_t symbol_update_message = 0;
    uint64_t system_state_message = 0;
    uint64_t security_trading_status_notification_message = 0;
    uint64_t symbol_clear_message = 0;
    uint64_t add_order_message = 0;
    uint64_t modify_order_message = 0;
    uint64_t delete_order_message = 0;
    uint64_t order_execution_message = 0;
    uint64_t trade_message = 0;
    uint64_t trade_cancel_message = 0;
    uint64_t sequenced_data_packet = 0;
    uint64_t unsequenced_data_packet = 0;
    uint64_t refresh_request_message = 0;
    uint64_t refresh_response_message = 0;
    uint64_t end_of_refresh_notification_message = 0;
    uint64_t login_request = 0;
    uint64_t login_response = 0;
    uint64_t synchronization_complete = 0;
    uint64_t retransmission_request = 0;
    uint64_t logout_request = 0;
    uint64_t goodbye_packet = 0;
    uint64_t test_packet = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {
        esesm_tcp_packet_reassembler.on_data = [this](const packet::TcpFlowKey& key, const std::byte* data, std::size_t length) { esesm_tcp_packet_flow(key, data, length); };
    }

    // process a frame: every tree carrying its transport reads it
    void udp() {
        const auto& frame = parser.frame();

        if (frame.is_udp()) {
            walk_mach_message(frame);
        }

        if (frame.is_tcp()) {
            esesm_tcp_packet_reassembler.process(frame);
        }
    }

    // walk the Udp Packet tree's datagrams
    void walk_mach_message(const packet::Frame& frame) {
        mach_message.initialize(frame.payload, frame.payload_len);

        while (mach_message.next()) {
            if (mach_message.mach_packet_type == 0 || mach_message.mach_packet_type == 1 || mach_message.mach_packet_type == 2) {
                ++heartbeats;
                continue;
            }

            process_mach_message(mach_message.message, mach_message.mach_packet_type);
        }
    }

    // walk the Tcp Packet tree's reassembled bytes
    void esesm_tcp_packet_flow(const packet::TcpFlowKey& key, const std::byte* data, std::size_t length) {
        auto& bytes = esesm_tcp_packet_flows[key];
        bytes.insert(bytes.end(),
                     reinterpret_cast<const std::uint8_t*>(data),
                     reinterpret_cast<const std::uint8_t*>(data) + length);

        const auto* base = reinterpret_cast<const std::byte*>(bytes.data());
        esesm_tcp_packet.initialize(base, bytes.size());

        std::size_t consumed = 0;

        while (esesm_tcp_packet.next()) {
            if (esesm_tcp_packet.current > esesm_tcp_packet.end) { break; }   // the packet's bytes have not all arrived

            consumed = static_cast<std::size_t>(esesm_tcp_packet.current - base);
            if (esesm_tcp_packet.esesm_packet_type == 'u' || esesm_tcp_packet.esesm_packet_type == '0' || esesm_tcp_packet.esesm_packet_type == '1') {
                ++heartbeats;
                continue;
            }

            process_esesm_tcp_packet(esesm_tcp_packet.message, esesm_tcp_packet.esesm_packet_type);
        }

        // drop what was read, keeping the packet that is still arriving
        if (consumed > 0) {
            bytes.erase(bytes.begin(), bytes.begin() + static_cast<std::ptrdiff_t>(consumed));
        }
    }

    // count a message of the Udp Packet tree
    void process_mach_message(const std::byte* pointer, const std::uint8_t mach_packet_type) {
        switch (mach_packet_type) {
            case 3:
                ++total_messages;
                ++application_message;
                {
                    const auto* sub_header = miax::pearlequities::depthofmarket::mach::v1_3_d::ApplicationMessage::parse(pointer);
                    const std::uint8_t message_type = sub_header->message_type.get();
                    switch (message_type) {
                        case 49:
                            ++system_time_message;
                            break;
                        case 1:
                            ++symbol_update_message;
                            break;
                        case 83:
                            ++system_state_message;
                            break;
                        case 4:
                            ++security_trading_status_notification_message;
                            break;
                        case 5:
                            ++symbol_clear_message;
                            break;
                        case 20:
                            ++add_order_message;
                            break;
                        case 21:
                            ++modify_order_message;
                            break;
                        case 23:
                            ++delete_order_message;
                            break;
                        case 24:
                            ++order_execution_message;
                            break;
                        case 10:
                            ++trade_message;
                            break;
                        case 11:
                            ++trade_cancel_message;
                            break;
                        default:
                            ++unknown_messages;
                            break;
                    }
                }
                break;

            default:
                ++total_messages;
                ++unknown_messages;
                if (options.verbose) {
                    std::cerr << "Unknown mach_packet_type: " << static_cast<int>(mach_packet_type) << std::endl;
                }
                break;
        }
    }

    // count a message of the Tcp Packet tree
    void process_esesm_tcp_packet(const std::byte* pointer, const char esesm_packet_type) {
        switch (esesm_packet_type) {
            case 's':
                ++total_messages;
                ++sequenced_data_packet;
                break;
            case 'U':
                ++total_messages;
                ++unsequenced_data_packet;
                {
                    const auto* sub_header = miax::pearlequities::depthofmarket::mach::v1_3_d::UnsequencedDataPacket::parse(pointer);
                    const char unsequenced_message_type = sub_header->unsequenced_message_type.get();
                    switch (unsequenced_message_type) {
                        case 'R':
                            ++refresh_request_message;
                            break;
                        case 'r':
                            ++refresh_response_message;
                            break;
                        case 'E':
                            ++end_of_refresh_notification_message;
                            break;
                        default:
                            ++unknown_messages;
                            break;
                    }
                }
                break;
            case 'l':
                ++total_messages;
                ++login_request;
                break;
            case 'r':
                ++total_messages;
                ++login_response;
                break;
            case 'c':
                ++total_messages;
                ++synchronization_complete;
                break;
            case 'a':
                ++total_messages;
                ++retransmission_request;
                break;
            case 'X':
                ++total_messages;
                ++logout_request;
                break;
            case 'G':
                ++total_messages;
                ++goodbye_packet;
                break;
            case 'T':
                ++total_messages;
                ++test_packet;
                break;

            default:
                ++total_messages;
                ++unknown_messages;
                if (options.verbose) {
                    std::cerr << "Unknown esesm_packet_type: " << static_cast<int>(esesm_packet_type) << std::endl;
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
        std::cout << "  ApplicationMessage (3)                        " << application_message << std::endl;
        std::cout << "  SystemTimeMessage (49)                        " << system_time_message << std::endl;
        std::cout << "  SymbolUpdateMessage (1)                       " << symbol_update_message << std::endl;
        std::cout << "  SystemStateMessage (83)                       " << system_state_message << std::endl;
        std::cout << "  SecurityTradingStatusNotificationMessage (4)  " << security_trading_status_notification_message << std::endl;
        std::cout << "  SymbolClearMessage (5)                        " << symbol_clear_message << std::endl;
        std::cout << "  AddOrderMessage (20)                          " << add_order_message << std::endl;
        std::cout << "  ModifyOrderMessage (21)                       " << modify_order_message << std::endl;
        std::cout << "  DeleteOrderMessage (23)                       " << delete_order_message << std::endl;
        std::cout << "  OrderExecutionMessage (24)                    " << order_execution_message << std::endl;
        std::cout << "  TradeMessage (10)                             " << trade_message << std::endl;
        std::cout << "  TradeCancelMessage (11)                       " << trade_cancel_message << std::endl;
        std::cout << "  SequencedDataPacket (s)                       " << sequenced_data_packet << std::endl;
        std::cout << "  UnsequencedDataPacket (U)                     " << unsequenced_data_packet << std::endl;
        std::cout << "  RefreshRequestMessage (R)                     " << refresh_request_message << std::endl;
        std::cout << "  RefreshResponseMessage (r)                    " << refresh_response_message << std::endl;
        std::cout << "  EndOfRefreshNotificationMessage (E)           " << end_of_refresh_notification_message << std::endl;
        std::cout << "  LoginRequest (l)                              " << login_request << std::endl;
        std::cout << "  LoginResponse (r)                             " << login_response << std::endl;
        std::cout << "  SynchronizationComplete (c)                   " << synchronization_complete << std::endl;
        std::cout << "  RetransmissionRequest (a)                     " << retransmission_request << std::endl;
        std::cout << "  LogoutRequest (X)                             " << logout_request << std::endl;
        std::cout << "  GoodbyePacket (G)                             " << goodbye_packet << std::endl;
        std::cout << "  TestPacket (T)                                " << test_packet << std::endl;
    }
};
}
