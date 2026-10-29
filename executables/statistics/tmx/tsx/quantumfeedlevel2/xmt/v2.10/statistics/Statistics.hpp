#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/modern/tmx/tsx/quantumfeedlevel2/xmt/v2.10/definitions.hpp"

namespace statistics {

// Tmx Xmt C++ statistics
struct Statistics {

    tmx::tsx::quantumfeedlevel2::xmt::v2_10::BodyIterator body;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t heartbeat_body = 0;
    uint64_t symbol_status_message = 0;
    uint64_t order_book_message = 0;
    uint64_t order_book_terms_message = 0;
    uint64_t assign_cop_orders_message = 0;
    uint64_t assign_cop_no_orders_message = 0;
    uint64_t assign_limit_message = 0;
    uint64_t market_state_update_message = 0;
    uint64_t moc_imbalance_message = 0;
    uint64_t order_booked_message = 0;
    uint64_t order_booked_terms_message = 0;
    uint64_t order_cancelled_message = 0;
    uint64_t order_cancelled_terms_message = 0;
    uint64_t order_price_time_assigned_message = 0;
    uint64_t order_price_time_assigned_terms_message = 0;
    uint64_t stock_status_message = 0;
    uint64_t trade_report_message = 0;
    uint64_t trade_report_terms_message = 0;
    uint64_t trade_cancelled_message = 0;
    uint64_t trade_cancelled_terms_message = 0;
    uint64_t trade_correction_message = 0;
    uint64_t trade_correction_terms_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process a frame: every tree carrying its transport reads it
    void udp() {
        const auto& frame = parser.frame();

        if (frame.is_udp()) {
            walk_body(frame);
        }
    }

    // walk the Packet tree's datagrams
    void walk_body(const packet::Frame& frame) {
        body.initialize(frame.payload, frame.payload_len);

        while (body.next()) {
            process_body(body.message, body.msg_type);
        }
    }

    // count a message of the Packet tree
    void process_body(const std::byte*, const char msg_type) {
        switch (msg_type) {
            case '0':
                ++total_messages;
                ++heartbeat_body;
                break;
            case 'J':
                ++total_messages;
                ++symbol_status_message;
                break;
            case 'G':
                ++total_messages;
                ++order_book_message;
                break;
            case 'j':
                ++total_messages;
                ++order_book_terms_message;
                break;
            case 'A':
                ++total_messages;
                ++assign_cop_orders_message;
                break;
            case 'B':
                ++total_messages;
                ++assign_cop_no_orders_message;
                break;
            case 'C':
                ++total_messages;
                ++assign_limit_message;
                break;
            case 'E':
                ++total_messages;
                ++market_state_update_message;
                break;
            case 'F':
                ++total_messages;
                ++moc_imbalance_message;
                break;
            case 'P':
                ++total_messages;
                ++order_booked_message;
                break;
            case 'm':
                ++total_messages;
                ++order_booked_terms_message;
                break;
            case 'Q':
                ++total_messages;
                ++order_cancelled_message;
                break;
            case 'n':
                ++total_messages;
                ++order_cancelled_terms_message;
                break;
            case 'R':
                ++total_messages;
                ++order_price_time_assigned_message;
                break;
            case 'o':
                ++total_messages;
                ++order_price_time_assigned_terms_message;
                break;
            case 'I':
                ++total_messages;
                ++stock_status_message;
                break;
            case 'S':
                ++total_messages;
                ++trade_report_message;
                break;
            case 'p':
                ++total_messages;
                ++trade_report_terms_message;
                break;
            case 'T':
                ++total_messages;
                ++trade_cancelled_message;
                break;
            case 'q':
                ++total_messages;
                ++trade_cancelled_terms_message;
                break;
            case 'U':
                ++total_messages;
                ++trade_correction_message;
                break;
            case 'r':
                ++total_messages;
                ++trade_correction_terms_message;
                break;

            default:
                ++total_messages;
                ++unknown_messages;
                if (options.verbose) {
                    std::cerr << "Unknown msg_type: " << static_cast<int>(msg_type) << std::endl;
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
        std::cout << "  HeartbeatBody (0)                       " << heartbeat_body << std::endl;
        std::cout << "  SymbolStatusMessage (J)                 " << symbol_status_message << std::endl;
        std::cout << "  OrderBookMessage (G)                    " << order_book_message << std::endl;
        std::cout << "  OrderBookTermsMessage (j)               " << order_book_terms_message << std::endl;
        std::cout << "  AssignCopOrdersMessage (A)              " << assign_cop_orders_message << std::endl;
        std::cout << "  AssignCopNoOrdersMessage (B)            " << assign_cop_no_orders_message << std::endl;
        std::cout << "  AssignLimitMessage (C)                  " << assign_limit_message << std::endl;
        std::cout << "  MarketStateUpdateMessage (E)            " << market_state_update_message << std::endl;
        std::cout << "  MocImbalanceMessage (F)                 " << moc_imbalance_message << std::endl;
        std::cout << "  OrderBookedMessage (P)                  " << order_booked_message << std::endl;
        std::cout << "  OrderBookedTermsMessage (m)             " << order_booked_terms_message << std::endl;
        std::cout << "  OrderCancelledMessage (Q)               " << order_cancelled_message << std::endl;
        std::cout << "  OrderCancelledTermsMessage (n)          " << order_cancelled_terms_message << std::endl;
        std::cout << "  OrderPriceTimeAssignedMessage (R)       " << order_price_time_assigned_message << std::endl;
        std::cout << "  OrderPriceTimeAssignedTermsMessage (o)  " << order_price_time_assigned_terms_message << std::endl;
        std::cout << "  StockStatusMessage (I)                  " << stock_status_message << std::endl;
        std::cout << "  TradeReportMessage (S)                  " << trade_report_message << std::endl;
        std::cout << "  TradeReportTermsMessage (p)             " << trade_report_terms_message << std::endl;
        std::cout << "  TradeCancelledMessage (T)               " << trade_cancelled_message << std::endl;
        std::cout << "  TradeCancelledTermsMessage (q)          " << trade_cancelled_terms_message << std::endl;
        std::cout << "  TradeCorrectionMessage (U)              " << trade_correction_message << std::endl;
        std::cout << "  TradeCorrectionTermsMessage (r)         " << trade_correction_terms_message << std::endl;
    }
};
}
