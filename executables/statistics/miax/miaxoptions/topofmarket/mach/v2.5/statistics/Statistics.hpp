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
#include "cpp/modern/miax/miaxoptions/topofmarket/mach/v2.5/definitions.hpp"

namespace statistics {

// Miax Mach C++ statistics
struct Statistics {

    miax::miaxoptions::topofmarket::mach::v2_5::UdpPacketIterator udp_packet;
    miax::miaxoptions::topofmarket::mach::v2_5::SesmTcpPacketIterator sesm_tcp_packet;
    packet::TcpReassembler sesm_tcp_packet_reassembler;
    std::unordered_map<packet::TcpFlowKey, std::vector<std::uint8_t>, packet::TcpFlowKey::hash> sesm_tcp_packet_flows;
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
    uint64_t simple_series_update_message = 0;
    uint64_t system_state_message = 0;
    uint64_t simple_top_of_market_best_bid_or_offer_compact_bid_message = 0;
    uint64_t simple_top_of_market_best_bid_or_offer_compact_offer_message = 0;
    uint64_t simple_top_of_market_best_bid_or_offer_wide_bid_message = 0;
    uint64_t simple_top_of_market_best_bid_or_offer_wide_offer_message = 0;
    uint64_t simple_double_sided_top_of_market_best_bid_or_offer_compact_message = 0;
    uint64_t simple_double_sided_top_of_market_best_bid_or_offer_wide_message = 0;
    uint64_t last_sale_message = 0;
    uint64_t trade_cancel_message = 0;
    uint64_t underlying_trading_status_notification_message = 0;
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
        sesm_tcp_packet_reassembler.on_data = [this](const packet::TcpFlowKey& key, const std::byte* data, std::size_t length) { sesm_tcp_packet_flow(key, data, length); };
    }

    // process a frame: every tree carrying its transport reads it
    void udp() {
        const auto& frame = parser.frame();

        if (frame.is_udp()) {
            walk_udp_packet(frame);
        }

        if (frame.is_tcp()) {
            sesm_tcp_packet_reassembler.process(frame);
        }
    }

    // walk the Udp Packet tree's datagrams
    void walk_udp_packet(const packet::Frame& frame) {
        udp_packet.initialize(frame.payload, frame.payload_len);

        while (udp_packet.next()) {
            if (udp_packet.packet_type == 0 || udp_packet.packet_type == 1 || udp_packet.packet_type == 2) {
                ++heartbeats;
                continue;
            }

            process_udp_packet(udp_packet.message, udp_packet.packet_type);
        }
    }

    // walk the Tcp Packet tree's reassembled bytes
    void sesm_tcp_packet_flow(const packet::TcpFlowKey& key, const std::byte* data, std::size_t length) {
        auto& bytes = sesm_tcp_packet_flows[key];
        bytes.insert(bytes.end(),
                     reinterpret_cast<const std::uint8_t*>(data),
                     reinterpret_cast<const std::uint8_t*>(data) + length);

        const auto* base = reinterpret_cast<const std::byte*>(bytes.data());
        sesm_tcp_packet.initialize(base, bytes.size());

        std::size_t consumed = 0;

        while (sesm_tcp_packet.next()) {
            if (sesm_tcp_packet.current > sesm_tcp_packet.end) { break; }   // the packet's bytes have not all arrived

            consumed = static_cast<std::size_t>(sesm_tcp_packet.current - base);
            if (sesm_tcp_packet.sesm_packet_type == 'u' || sesm_tcp_packet.sesm_packet_type == '0' || sesm_tcp_packet.sesm_packet_type == '1') {
                ++heartbeats;
                continue;
            }

            process_sesm_tcp_packet(sesm_tcp_packet.message, sesm_tcp_packet.sesm_packet_type);
        }

        // drop what was read, keeping the packet that is still arriving
        if (consumed > 0) {
            bytes.erase(bytes.begin(), bytes.begin() + static_cast<std::ptrdiff_t>(consumed));
        }
    }

    // count a message of the Udp Packet tree
    void process_udp_packet(const std::byte* pointer, const std::uint8_t packet_type) {
        switch (packet_type) {
            case 3:
                ++total_messages;
                ++application_message;
                {
                    const auto* sub_header = miax::miaxoptions::topofmarket::mach::v2_5::ApplicationMessage::parse(pointer);
                    const char message_type = sub_header->message_type.get();
                    switch (message_type) {
                        case '1':
                            ++system_time_message;
                            break;
                        case 'P':
                            ++simple_series_update_message;
                            break;
                        case 'S':
                            ++system_state_message;
                            break;
                        case 'B':
                            ++simple_top_of_market_best_bid_or_offer_compact_bid_message;
                            break;
                        case 'O':
                            ++simple_top_of_market_best_bid_or_offer_compact_offer_message;
                            break;
                        case 'b':
                            ++simple_top_of_market_best_bid_or_offer_wide_bid_message;
                            break;
                        case 'o':
                            ++simple_top_of_market_best_bid_or_offer_wide_offer_message;
                            break;
                        case 'd':
                            ++simple_double_sided_top_of_market_best_bid_or_offer_compact_message;
                            break;
                        case 'D':
                            ++simple_double_sided_top_of_market_best_bid_or_offer_wide_message;
                            break;
                        case 'T':
                            ++last_sale_message;
                            break;
                        case 'X':
                            ++trade_cancel_message;
                            break;
                        case 'H':
                            ++underlying_trading_status_notification_message;
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
                    std::cerr << "Unknown packet_type: " << static_cast<int>(packet_type) << std::endl;
                }
                break;
        }
    }

    // count a message of the Tcp Packet tree
    void process_sesm_tcp_packet(const std::byte* pointer, const char sesm_packet_type) {
        switch (sesm_packet_type) {
            case 's':
                ++total_messages;
                ++sequenced_data_packet;
                break;
            case 'U':
                ++total_messages;
                ++unsequenced_data_packet;
                {
                    const auto* sub_header = miax::miaxoptions::topofmarket::mach::v2_5::UnsequencedDataPacket::parse(pointer);
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
                    std::cerr << "Unknown sesm_packet_type: " << static_cast<int>(sesm_packet_type) << std::endl;
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
        std::cout << "  ApplicationMessage (3)                                        " << application_message << std::endl;
        std::cout << "  SystemTimeMessage (1)                                         " << system_time_message << std::endl;
        std::cout << "  SimpleSeriesUpdateMessage (P)                                 " << simple_series_update_message << std::endl;
        std::cout << "  SystemStateMessage (S)                                        " << system_state_message << std::endl;
        std::cout << "  SimpleTopOfMarketBestBidOrOfferCompactBidMessage (B)          " << simple_top_of_market_best_bid_or_offer_compact_bid_message << std::endl;
        std::cout << "  SimpleTopOfMarketBestBidOrOfferCompactOfferMessage (O)        " << simple_top_of_market_best_bid_or_offer_compact_offer_message << std::endl;
        std::cout << "  SimpleTopOfMarketBestBidOrOfferWideBidMessage (b)             " << simple_top_of_market_best_bid_or_offer_wide_bid_message << std::endl;
        std::cout << "  SimpleTopOfMarketBestBidOrOfferWideOfferMessage (o)           " << simple_top_of_market_best_bid_or_offer_wide_offer_message << std::endl;
        std::cout << "  SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage (d)  " << simple_double_sided_top_of_market_best_bid_or_offer_compact_message << std::endl;
        std::cout << "  SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage (D)     " << simple_double_sided_top_of_market_best_bid_or_offer_wide_message << std::endl;
        std::cout << "  LastSaleMessage (T)                                           " << last_sale_message << std::endl;
        std::cout << "  TradeCancelMessage (X)                                        " << trade_cancel_message << std::endl;
        std::cout << "  UnderlyingTradingStatusNotificationMessage (H)                " << underlying_trading_status_notification_message << std::endl;
        std::cout << "  SequencedDataPacket (s)                                       " << sequenced_data_packet << std::endl;
        std::cout << "  UnsequencedDataPacket (U)                                     " << unsequenced_data_packet << std::endl;
        std::cout << "  RefreshRequestMessage (R)                                     " << refresh_request_message << std::endl;
        std::cout << "  RefreshResponseMessage (r)                                    " << refresh_response_message << std::endl;
        std::cout << "  EndOfRefreshNotificationMessage (E)                           " << end_of_refresh_notification_message << std::endl;
        std::cout << "  LoginRequest (l)                                              " << login_request << std::endl;
        std::cout << "  LoginResponse (r)                                             " << login_response << std::endl;
        std::cout << "  SynchronizationComplete (c)                                   " << synchronization_complete << std::endl;
        std::cout << "  RetransmissionRequest (a)                                     " << retransmission_request << std::endl;
        std::cout << "  LogoutRequest (X)                                             " << logout_request << std::endl;
        std::cout << "  GoodbyePacket (G)                                             " << goodbye_packet << std::endl;
        std::cout << "  TestPacket (T)                                                " << test_packet << std::endl;
    }
};
}
