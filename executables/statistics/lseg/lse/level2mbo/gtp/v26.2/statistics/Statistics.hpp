#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/modern/lseg/lse/level2mbo/gtp/v26.2/definitions.hpp"

namespace statistics {

// Lseg Gtp C++ statistics
struct Statistics {

    lseg::lse::level2mbo::gtp::v26_2::MessageIterator message;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t system_event_message = 0;
    uint64_t instrument_directory_message = 0;
    uint64_t instrument_status_message = 0;
    uint64_t add_order_mbo_message = 0;
    uint64_t add_order_short_mbo_message = 0;
    uint64_t order_book_clear_message = 0;
    uint64_t trade_message = 0;
    uint64_t statistics_message = 0;
    uint64_t statistics_update_message = 0;

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
    void process_message(const std::byte*, const std::uint8_t message_type) {
        switch (message_type) {
            case 0x53:
                ++total_messages;
                ++system_event_message;
                break;
            case 0x70:
                ++total_messages;
                ++instrument_directory_message;
                break;
            case 0x48:
                ++total_messages;
                ++instrument_status_message;
                break;
            case 0x41:
                ++total_messages;
                ++add_order_mbo_message;
                break;
            case 0x65:
                ++total_messages;
                ++add_order_short_mbo_message;
                break;
            case 0x79:
                ++total_messages;
                ++order_book_clear_message;
                break;
            case 0x50:
                ++total_messages;
                ++trade_message;
                break;
            case 0x77:
                ++total_messages;
                ++statistics_message;
                break;
            case 0x6A:
                ++total_messages;
                ++statistics_update_message;
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
        std::cout << "  SystemEventMessage (0x53)          " << system_event_message << std::endl;
        std::cout << "  InstrumentDirectoryMessage (0x70)  " << instrument_directory_message << std::endl;
        std::cout << "  InstrumentStatusMessage (0x48)     " << instrument_status_message << std::endl;
        std::cout << "  AddOrderMboMessage (0x41)          " << add_order_mbo_message << std::endl;
        std::cout << "  AddOrderShortMboMessage (0x65)     " << add_order_short_mbo_message << std::endl;
        std::cout << "  OrderBookClearMessage (0x79)       " << order_book_clear_message << std::endl;
        std::cout << "  TradeMessage (0x50)                " << trade_message << std::endl;
        std::cout << "  StatisticsMessage (0x77)           " << statistics_message << std::endl;
        std::cout << "  StatisticsUpdateMessage (0x6A)     " << statistics_update_message << std::endl;
    }
};
}
