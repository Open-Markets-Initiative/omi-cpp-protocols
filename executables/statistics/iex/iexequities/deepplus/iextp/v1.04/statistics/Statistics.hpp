#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/modern/iex/iexequities/deepplus/iextp/v1.04/definitions.hpp"

namespace statistics {

// Iex IexTp C++ statistics
struct Statistics {

    iex::iexequities::deepplus::iextp::v1_04::MessageIterator message;
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
    uint64_t security_directory_message = 0;
    uint64_t trading_status_message = 0;
    uint64_t retail_liquidity_indicator_message = 0;
    uint64_t operational_halt_status_message = 0;
    uint64_t short_sale_price_test_status_message = 0;
    uint64_t security_event_message = 0;
    uint64_t add_order_message = 0;
    uint64_t order_modify_message = 0;
    uint64_t order_delete_message = 0;
    uint64_t order_executed_message = 0;
    uint64_t trade_message = 0;
    uint64_t trade_break_message = 0;
    uint64_t clear_book_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet
    void udp() {
        const auto& frame = parser.frame();
        message.initialize(frame.payload, frame.payload_len);

        if (message.message_count == 0) {
            ++heartbeats;
            return;
        }

        while (message.next()) {
            process(message.message, message.message_type);
        }
    }

    // process message
    void process(const std::byte* pointer, const char message_type) {
        ++total_messages;

        switch (message_type) {
            case 'S':
                ++system_event_message;
                break;
            case 'D':
                ++security_directory_message;
                break;
            case 'H':
                ++trading_status_message;
                break;
            case 'I':
                ++retail_liquidity_indicator_message;
                break;
            case 'O':
                ++operational_halt_status_message;
                break;
            case 'P':
                ++short_sale_price_test_status_message;
                break;
            case 'E':
                ++security_event_message;
                break;
            case 'a':
                ++add_order_message;
                break;
            case 'M':
                ++order_modify_message;
                break;
            case 'R':
                ++order_delete_message;
                break;
            case 'L':
                ++order_executed_message;
                break;
            case 'T':
                ++trade_message;
                break;
            case 'B':
                ++trade_break_message;
                break;
            case 'C':
                ++clear_book_message;
                break;

            default:
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
        std::cout << "  SystemEventMessage (S)               " << system_event_message << std::endl;
        std::cout << "  SecurityDirectoryMessage (D)         " << security_directory_message << std::endl;
        std::cout << "  TradingStatusMessage (H)             " << trading_status_message << std::endl;
        std::cout << "  RetailLiquidityIndicatorMessage (I)  " << retail_liquidity_indicator_message << std::endl;
        std::cout << "  OperationalHaltStatusMessage (O)     " << operational_halt_status_message << std::endl;
        std::cout << "  ShortSalePriceTestStatusMessage (P)  " << short_sale_price_test_status_message << std::endl;
        std::cout << "  SecurityEventMessage (E)             " << security_event_message << std::endl;
        std::cout << "  AddOrderMessage (a)                  " << add_order_message << std::endl;
        std::cout << "  OrderModifyMessage (M)               " << order_modify_message << std::endl;
        std::cout << "  OrderDeleteMessage (R)               " << order_delete_message << std::endl;
        std::cout << "  OrderExecutedMessage (L)             " << order_executed_message << std::endl;
        std::cout << "  TradeMessage (T)                     " << trade_message << std::endl;
        std::cout << "  TradeBreakMessage (B)                " << trade_break_message << std::endl;
        std::cout << "  ClearBookMessage (C)                 " << clear_book_message << std::endl;
    }
};
}
