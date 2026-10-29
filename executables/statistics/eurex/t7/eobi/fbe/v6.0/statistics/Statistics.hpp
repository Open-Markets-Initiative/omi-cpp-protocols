#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/modern/eurex/t7/eobi/fbe/v6.0/definitions.hpp"

namespace statistics {

// Eurex Fbe C++ statistics
struct Statistics {

    eurex::t7::eobi::fbe::v6_0::MessageIterator message;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t add_complex_instrument = 0;
    uint64_t auction_bbo = 0;
    uint64_t auction_clearing_price = 0;
    uint64_t cross_request = 0;
    uint64_t execution_summary = 0;
    uint64_t full_order_execution = 0;
    uint64_t heartbeat = 0;
    uint64_t instrument_state_change = 0;
    uint64_t instrument_summary = 0;
    uint64_t order_add = 0;
    uint64_t order_delete = 0;
    uint64_t order_mass_delete = 0;
    uint64_t order_modify = 0;
    uint64_t order_modify_same_prio = 0;
    uint64_t partial_order_execution = 0;
    uint64_t product_state_change = 0;
    uint64_t product_summary = 0;
    uint64_t quote_request = 0;
    uint64_t snapshot_order = 0;
    uint64_t top_of_book = 0;
    uint64_t trade_report = 0;
    uint64_t trade_reversal = 0;

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
            process_message(message.message, message.template_id);
        }
    }

    // count a message of the Packet tree
    void process_message(const std::byte*, const std::uint16_t template_id) {
        switch (template_id) {
            case 13400:
                ++total_messages;
                ++add_complex_instrument;
                break;
            case 13500:
                ++total_messages;
                ++auction_bbo;
                break;
            case 13501:
                ++total_messages;
                ++auction_clearing_price;
                break;
            case 13502:
                ++total_messages;
                ++cross_request;
                break;
            case 13202:
                ++total_messages;
                ++execution_summary;
                break;
            case 13104:
                ++total_messages;
                ++full_order_execution;
                break;
            case 13001:
                ++total_messages;
                ++heartbeat;
                break;
            case 13301:
                ++total_messages;
                ++instrument_state_change;
                break;
            case 13601:
                ++total_messages;
                ++instrument_summary;
                break;
            case 13100:
                ++total_messages;
                ++order_add;
                break;
            case 13102:
                ++total_messages;
                ++order_delete;
                break;
            case 13103:
                ++total_messages;
                ++order_mass_delete;
                break;
            case 13101:
                ++total_messages;
                ++order_modify;
                break;
            case 13106:
                ++total_messages;
                ++order_modify_same_prio;
                break;
            case 13105:
                ++total_messages;
                ++partial_order_execution;
                break;
            case 13300:
                ++total_messages;
                ++product_state_change;
                break;
            case 13600:
                ++total_messages;
                ++product_summary;
                break;
            case 13503:
                ++total_messages;
                ++quote_request;
                break;
            case 13602:
                ++total_messages;
                ++snapshot_order;
                break;
            case 13504:
                ++total_messages;
                ++top_of_book;
                break;
            case 13201:
                ++total_messages;
                ++trade_report;
                break;
            case 13200:
                ++total_messages;
                ++trade_reversal;
                break;

            default:
                ++total_messages;
                ++unknown_messages;
                if (options.verbose) {
                    std::cerr << "Unknown template_id: " << static_cast<int>(template_id) << std::endl;
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
        std::cout << "  AddComplexInstrument (13400)   " << add_complex_instrument << std::endl;
        std::cout << "  AuctionBbo (13500)             " << auction_bbo << std::endl;
        std::cout << "  AuctionClearingPrice (13501)   " << auction_clearing_price << std::endl;
        std::cout << "  CrossRequest (13502)           " << cross_request << std::endl;
        std::cout << "  ExecutionSummary (13202)       " << execution_summary << std::endl;
        std::cout << "  FullOrderExecution (13104)     " << full_order_execution << std::endl;
        std::cout << "  Heartbeat (13001)              " << heartbeat << std::endl;
        std::cout << "  InstrumentStateChange (13301)  " << instrument_state_change << std::endl;
        std::cout << "  InstrumentSummary (13601)      " << instrument_summary << std::endl;
        std::cout << "  OrderAdd (13100)               " << order_add << std::endl;
        std::cout << "  OrderDelete (13102)            " << order_delete << std::endl;
        std::cout << "  OrderMassDelete (13103)        " << order_mass_delete << std::endl;
        std::cout << "  OrderModify (13101)            " << order_modify << std::endl;
        std::cout << "  OrderModifySamePrio (13106)    " << order_modify_same_prio << std::endl;
        std::cout << "  PartialOrderExecution (13105)  " << partial_order_execution << std::endl;
        std::cout << "  ProductStateChange (13300)     " << product_state_change << std::endl;
        std::cout << "  ProductSummary (13600)         " << product_summary << std::endl;
        std::cout << "  QuoteRequest (13503)           " << quote_request << std::endl;
        std::cout << "  SnapshotOrder (13602)          " << snapshot_order << std::endl;
        std::cout << "  TopOfBook (13504)              " << top_of_book << std::endl;
        std::cout << "  TradeReport (13201)            " << trade_report << std::endl;
        std::cout << "  TradeReversal (13200)          " << trade_reversal << std::endl;
    }
};
}
