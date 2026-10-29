#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/modern/nyse/nyseequities/imbalancesfeed/xdp/v2.2.a/definitions.hpp"

namespace statistics {

// Nyse Xdp C++ statistics
struct Statistics {

    nyse::nyseequities::imbalancesfeed::xdp::v2_2_a::MessageIterator message;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t sequence_number_reset_message = 0;
    uint64_t symbol_index_mapping_message = 0;
    uint64_t retransmission_request_message = 0;
    uint64_t request_response_message = 0;
    uint64_t heartbeat_response_message = 0;
    uint64_t symbol_index_mapping_request_message = 0;
    uint64_t refresh_request_message = 0;
    uint64_t message_unavailable_message = 0;
    uint64_t symbol_clear_message = 0;
    uint64_t security_status_message = 0;
    uint64_t refresh_header_message = 0;
    uint64_t imbalance_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process a frame: every tree carrying its transport reads it
    void udp() {
        const auto& frame = parser.frame();

        if (frame.is_udp()) {
            walk_message(frame);
        }
    }

    // walk the Packet tree's datagrams
    void walk_message(const packet::Frame& frame) {
        message.initialize(frame.payload, frame.payload_len);

        while (message.next()) {
            process_message(message.message, message.message_type);
        }
    }

    // count a message of the Packet tree
    void process_message(const std::byte*, const std::uint16_t message_type) {
        switch (message_type) {
            case 1:
                ++total_messages;
                ++sequence_number_reset_message;
                break;
            case 3:
                ++total_messages;
                ++symbol_index_mapping_message;
                break;
            case 10:
                ++total_messages;
                ++retransmission_request_message;
                break;
            case 11:
                ++total_messages;
                ++request_response_message;
                break;
            case 12:
                ++total_messages;
                ++heartbeat_response_message;
                break;
            case 13:
                ++total_messages;
                ++symbol_index_mapping_request_message;
                break;
            case 15:
                ++total_messages;
                ++refresh_request_message;
                break;
            case 31:
                ++total_messages;
                ++message_unavailable_message;
                break;
            case 32:
                ++total_messages;
                ++symbol_clear_message;
                break;
            case 34:
                ++total_messages;
                ++security_status_message;
                break;
            case 35:
                ++total_messages;
                ++refresh_header_message;
                break;
            case 105:
                ++total_messages;
                ++imbalance_message;
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
        std::cout << "  SequenceNumberResetMessage (1)         " << sequence_number_reset_message << std::endl;
        std::cout << "  SymbolIndexMappingMessage (3)          " << symbol_index_mapping_message << std::endl;
        std::cout << "  RetransmissionRequestMessage (10)      " << retransmission_request_message << std::endl;
        std::cout << "  RequestResponseMessage (11)            " << request_response_message << std::endl;
        std::cout << "  HeartbeatResponseMessage (12)          " << heartbeat_response_message << std::endl;
        std::cout << "  SymbolIndexMappingRequestMessage (13)  " << symbol_index_mapping_request_message << std::endl;
        std::cout << "  RefreshRequestMessage (15)             " << refresh_request_message << std::endl;
        std::cout << "  MessageUnavailableMessage (31)         " << message_unavailable_message << std::endl;
        std::cout << "  SymbolClearMessage (32)                " << symbol_clear_message << std::endl;
        std::cout << "  SecurityStatusMessage (34)             " << security_status_message << std::endl;
        std::cout << "  RefreshHeaderMessage (35)              " << refresh_header_message << std::endl;
        std::cout << "  ImbalanceMessage (105)                 " << imbalance_message << std::endl;
    }
};
}
