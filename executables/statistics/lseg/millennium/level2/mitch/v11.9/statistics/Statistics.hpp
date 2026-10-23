#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/modern/lseg/millennium/level2/mitch/v11.9/definitions.hpp"

namespace statistics {

// Lseg Mitch C++ statistics
struct Statistics {

    lseg::millennium::level2::mitch::v11_9::MessageIterator message;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t time_message = 0;
    uint64_t system_event_message = 0;
    uint64_t symbol_directory_message = 0;
    uint64_t symbol_status_message = 0;
    uint64_t add_order_message = 0;
    uint64_t add_attributed_order_message = 0;
    uint64_t order_deleted_message = 0;
    uint64_t order_modified_message = 0;
    uint64_t order_book_clear_message = 0;
    uint64_t order_executed_message = 0;
    uint64_t order_executed_with_price_size_message = 0;
    uint64_t trade_message = 0;
    uint64_t auction_trade_message = 0;
    uint64_t auction_info_message = 0;
    uint64_t statistics_message = 0;
    uint64_t top_of_book_message = 0;

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
            case 0x54:
                ++total_messages;
                ++time_message;
                break;
            case 0x53:
                ++total_messages;
                ++system_event_message;
                break;
            case 0x52:
                ++total_messages;
                ++symbol_directory_message;
                break;
            case 0x48:
                ++total_messages;
                ++symbol_status_message;
                break;
            case 0x41:
                ++total_messages;
                ++add_order_message;
                break;
            case 0x46:
                ++total_messages;
                ++add_attributed_order_message;
                break;
            case 0x44:
                ++total_messages;
                ++order_deleted_message;
                break;
            case 0x55:
                ++total_messages;
                ++order_modified_message;
                break;
            case 0x79:
                ++total_messages;
                ++order_book_clear_message;
                break;
            case 0x45:
                ++total_messages;
                ++order_executed_message;
                break;
            case 0x43:
                ++total_messages;
                ++order_executed_with_price_size_message;
                break;
            case 0x50:
                ++total_messages;
                ++trade_message;
                break;
            case 0x51:
                ++total_messages;
                ++auction_trade_message;
                break;
            case 0x49:
                ++total_messages;
                ++auction_info_message;
                break;
            case 0x77:
                ++total_messages;
                ++statistics_message;
                break;
            case 0x71:
                ++total_messages;
                ++top_of_book_message;
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
        std::cout << "  TimeMessage (0x54)                        " << time_message << std::endl;
        std::cout << "  SystemEventMessage (0x53)                 " << system_event_message << std::endl;
        std::cout << "  SymbolDirectoryMessage (0x52)             " << symbol_directory_message << std::endl;
        std::cout << "  SymbolStatusMessage (0x48)                " << symbol_status_message << std::endl;
        std::cout << "  AddOrderMessage (0x41)                    " << add_order_message << std::endl;
        std::cout << "  AddAttributedOrderMessage (0x46)          " << add_attributed_order_message << std::endl;
        std::cout << "  OrderDeletedMessage (0x44)                " << order_deleted_message << std::endl;
        std::cout << "  OrderModifiedMessage (0x55)               " << order_modified_message << std::endl;
        std::cout << "  OrderBookClearMessage (0x79)              " << order_book_clear_message << std::endl;
        std::cout << "  OrderExecutedMessage (0x45)               " << order_executed_message << std::endl;
        std::cout << "  OrderExecutedWithPriceSizeMessage (0x43)  " << order_executed_with_price_size_message << std::endl;
        std::cout << "  TradeMessage (0x50)                       " << trade_message << std::endl;
        std::cout << "  AuctionTradeMessage (0x51)                " << auction_trade_message << std::endl;
        std::cout << "  AuctionInfoMessage (0x49)                 " << auction_info_message << std::endl;
        std::cout << "  StatisticsMessage (0x77)                  " << statistics_message << std::endl;
        std::cout << "  TopOfBookMessage (0x71)                   " << top_of_book_message << std::endl;
    }
};
}
