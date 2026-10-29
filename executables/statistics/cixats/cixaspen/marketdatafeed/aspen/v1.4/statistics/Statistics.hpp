#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/modern/cixats/cixaspen/marketdatafeed/aspen/v1.4/definitions.hpp"

namespace statistics {

// CixAts Aspen C++ statistics
struct Statistics {

    cixats::cixaspen::marketdatafeed::aspen::v1_4::MessageIterator message;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t market_event_message = 0;
    uint64_t symbol_information_message = 0;
    uint64_t symbol_state_message = 0;
    uint64_t new_order_add_message = 0;
    uint64_t order_partial_cancel_message = 0;
    uint64_t order_cancel_all_message = 0;
    uint64_t order_executed_message = 0;
    uint64_t trade_message = 0;
    uint64_t trade_cancel_message = 0;
    uint64_t trade_correct_message = 0;

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
    void process_message(const std::byte*, const char message_type) {
        switch (message_type) {
            case 'A':
                ++total_messages;
                ++market_event_message;
                break;
            case 'B':
                ++total_messages;
                ++symbol_information_message;
                break;
            case 'C':
                ++total_messages;
                ++symbol_state_message;
                break;
            case 'D':
                ++total_messages;
                ++new_order_add_message;
                break;
            case 'F':
                ++total_messages;
                ++order_partial_cancel_message;
                break;
            case 'G':
                ++total_messages;
                ++order_cancel_all_message;
                break;
            case 'J':
                ++total_messages;
                ++order_executed_message;
                break;
            case 'K':
                ++total_messages;
                ++trade_message;
                break;
            case 'L':
                ++total_messages;
                ++trade_cancel_message;
                break;
            case 'M':
                ++total_messages;
                ++trade_correct_message;
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
        std::cout << "  MarketEventMessage (A)         " << market_event_message << std::endl;
        std::cout << "  SymbolInformationMessage (B)   " << symbol_information_message << std::endl;
        std::cout << "  SymbolStateMessage (C)         " << symbol_state_message << std::endl;
        std::cout << "  NewOrderAddMessage (D)         " << new_order_add_message << std::endl;
        std::cout << "  OrderPartialCancelMessage (F)  " << order_partial_cancel_message << std::endl;
        std::cout << "  OrderCancelAllMessage (G)      " << order_cancel_all_message << std::endl;
        std::cout << "  OrderExecutedMessage (J)       " << order_executed_message << std::endl;
        std::cout << "  TradeMessage (K)               " << trade_message << std::endl;
        std::cout << "  TradeCancelMessage (L)         " << trade_cancel_message << std::endl;
        std::cout << "  TradeCorrectMessage (M)        " << trade_correct_message << std::endl;
    }
};
}
