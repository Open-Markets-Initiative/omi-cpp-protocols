#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/modern/nyse/amexoptions/complexfeed/xdp/v1.3.a/definitions.hpp"

namespace statistics {

// Nyse Xdp C++ statistics
struct Statistics {

    nyse::amexoptions::complexfeed::xdp::v1_3_a::MessageIterator message;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t complex_quote_message = 0;
    uint64_t complex_trade_message = 0;
    uint64_t complex_crossing_rfq_message = 0;
    uint64_t complex_cube_rfq_message = 0;
    uint64_t complex_status_message = 0;
    uint64_t refresh_complex_quote_message = 0;
    uint64_t refresh_complex_trade_message = 0;
    uint64_t complex_symbol_definition_message = 0;
    uint64_t stream_id_message = 0;
    uint64_t sequence_number_reset_message = 0;

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
            case 423:
                ++total_messages;
                ++complex_quote_message;
                break;
            case 425:
                ++total_messages;
                ++complex_trade_message;
                break;
            case 429:
                ++total_messages;
                ++complex_crossing_rfq_message;
                break;
            case 472:
                ++total_messages;
                ++complex_cube_rfq_message;
                break;
            case 433:
                ++total_messages;
                ++complex_status_message;
                break;
            case 511:
                ++total_messages;
                ++refresh_complex_quote_message;
                break;
            case 513:
                ++total_messages;
                ++refresh_complex_trade_message;
                break;
            case 439:
                ++total_messages;
                ++complex_symbol_definition_message;
                break;
            case 455:
                ++total_messages;
                ++stream_id_message;
                break;
            case 1:
                ++total_messages;
                ++sequence_number_reset_message;
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
        std::cout << "  ComplexQuoteMessage (423)             " << complex_quote_message << std::endl;
        std::cout << "  ComplexTradeMessage (425)             " << complex_trade_message << std::endl;
        std::cout << "  ComplexCrossingRfqMessage (429)       " << complex_crossing_rfq_message << std::endl;
        std::cout << "  ComplexCubeRfqMessage (472)           " << complex_cube_rfq_message << std::endl;
        std::cout << "  ComplexStatusMessage (433)            " << complex_status_message << std::endl;
        std::cout << "  RefreshComplexQuoteMessage (511)      " << refresh_complex_quote_message << std::endl;
        std::cout << "  RefreshComplexTradeMessage (513)      " << refresh_complex_trade_message << std::endl;
        std::cout << "  ComplexSymbolDefinitionMessage (439)  " << complex_symbol_definition_message << std::endl;
        std::cout << "  StreamIdMessage (455)                 " << stream_id_message << std::endl;
        std::cout << "  SequenceNumberResetMessage (1)        " << sequence_number_reset_message << std::endl;
    }
};
}
