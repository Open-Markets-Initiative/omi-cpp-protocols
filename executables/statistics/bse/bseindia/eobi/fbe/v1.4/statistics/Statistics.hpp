#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/modern/bse/bseindia/eobi/fbe/v1.4/definitions.hpp"

namespace statistics {

// Bse Fbe C++ statistics
struct Statistics {

    bse::bseindia::eobi::fbe::v1_4::MessageIterator message;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t heartbeat_message = 0;
    uint64_t product_summary_message = 0;
    uint64_t snapshot_order_message = 0;
    uint64_t instrument_summary_message = 0;
    uint64_t auction_best_bid_offer_message = 0;
    uint64_t auction_clearing_price_message = 0;
    uint64_t top_of_book_message = 0;
    uint64_t order_add_message = 0;
    uint64_t order_modify_message = 0;
    uint64_t order_modify_same_priority_message = 0;
    uint64_t order_delete_message = 0;
    uint64_t order_mass_delete_message = 0;
    uint64_t partial_order_execution_message = 0;
    uint64_t full_order_execution_message = 0;
    uint64_t trade_reversal_message = 0;
    uint64_t execution_summary_message = 0;
    uint64_t instrument_info_message = 0;
    uint64_t lpp_range_message = 0;
    uint64_t product_state_change_message = 0;
    uint64_t instrument_state_change_message = 0;
    uint64_t add_complex_instrument_message = 0;

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
            case 13001:
                ++total_messages;
                ++heartbeat_message;
                break;
            case 13600:
                ++total_messages;
                ++product_summary_message;
                break;
            case 13602:
                ++total_messages;
                ++snapshot_order_message;
                break;
            case 13601:
                ++total_messages;
                ++instrument_summary_message;
                break;
            case 13500:
                ++total_messages;
                ++auction_best_bid_offer_message;
                break;
            case 13501:
                ++total_messages;
                ++auction_clearing_price_message;
                break;
            case 13504:
                ++total_messages;
                ++top_of_book_message;
                break;
            case 13100:
                ++total_messages;
                ++order_add_message;
                break;
            case 13101:
                ++total_messages;
                ++order_modify_message;
                break;
            case 13106:
                ++total_messages;
                ++order_modify_same_priority_message;
                break;
            case 13102:
                ++total_messages;
                ++order_delete_message;
                break;
            case 13103:
                ++total_messages;
                ++order_mass_delete_message;
                break;
            case 13105:
                ++total_messages;
                ++partial_order_execution_message;
                break;
            case 13104:
                ++total_messages;
                ++full_order_execution_message;
                break;
            case 13200:
                ++total_messages;
                ++trade_reversal_message;
                break;
            case 13202:
                ++total_messages;
                ++execution_summary_message;
                break;
            case 13203:
                ++total_messages;
                ++instrument_info_message;
                break;
            case 13204:
                ++total_messages;
                ++lpp_range_message;
                break;
            case 13300:
                ++total_messages;
                ++product_state_change_message;
                break;
            case 13301:
                ++total_messages;
                ++instrument_state_change_message;
                break;
            case 13400:
                ++total_messages;
                ++add_complex_instrument_message;
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
        std::cout << "  HeartbeatMessage (13001)                " << heartbeat_message << std::endl;
        std::cout << "  ProductSummaryMessage (13600)           " << product_summary_message << std::endl;
        std::cout << "  SnapshotOrderMessage (13602)            " << snapshot_order_message << std::endl;
        std::cout << "  InstrumentSummaryMessage (13601)        " << instrument_summary_message << std::endl;
        std::cout << "  AuctionBestBidOfferMessage (13500)      " << auction_best_bid_offer_message << std::endl;
        std::cout << "  AuctionClearingPriceMessage (13501)     " << auction_clearing_price_message << std::endl;
        std::cout << "  TopOfBookMessage (13504)                " << top_of_book_message << std::endl;
        std::cout << "  OrderAddMessage (13100)                 " << order_add_message << std::endl;
        std::cout << "  OrderModifyMessage (13101)              " << order_modify_message << std::endl;
        std::cout << "  OrderModifySamePriorityMessage (13106)  " << order_modify_same_priority_message << std::endl;
        std::cout << "  OrderDeleteMessage (13102)              " << order_delete_message << std::endl;
        std::cout << "  OrderMassDeleteMessage (13103)          " << order_mass_delete_message << std::endl;
        std::cout << "  PartialOrderExecutionMessage (13105)    " << partial_order_execution_message << std::endl;
        std::cout << "  FullOrderExecutionMessage (13104)       " << full_order_execution_message << std::endl;
        std::cout << "  TradeReversalMessage (13200)            " << trade_reversal_message << std::endl;
        std::cout << "  ExecutionSummaryMessage (13202)         " << execution_summary_message << std::endl;
        std::cout << "  InstrumentInfoMessage (13203)           " << instrument_info_message << std::endl;
        std::cout << "  LppRangeMessage (13204)                 " << lpp_range_message << std::endl;
        std::cout << "  ProductStateChangeMessage (13300)       " << product_state_change_message << std::endl;
        std::cout << "  InstrumentStateChangeMessage (13301)    " << instrument_state_change_message << std::endl;
        std::cout << "  AddComplexInstrumentMessage (13400)     " << add_complex_instrument_message << std::endl;
    }
};
}
