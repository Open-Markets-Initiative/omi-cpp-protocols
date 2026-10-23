#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/advanced/nyse/arcaequities/integratedfeed/pillar/v2.5.g/messages/session.hpp"

namespace statistics {

// Nyse Pillar C++ statistics
struct Statistics {

    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;
    // messages dispatch recognised; the rest of total_messages is unknown
    uint64_t matched_messages = 0;

    // message counters
    uint64_t sequence_number_reset_message = 0;
    uint64_t source_time_reference_message = 0;
    uint64_t symbol_index_mapping_message = 0;
    uint64_t symbol_clear_message = 0;
    uint64_t security_status_message = 0;
    uint64_t add_order_message = 0;
    uint64_t modify_order_message = 0;
    uint64_t delete_order_message = 0;
    uint64_t order_execution_message = 0;
    uint64_t replace_order_message = 0;
    uint64_t imbalance_message = 0;
    uint64_t add_order_refresh_message = 0;
    uint64_t non_displayed_trade_message = 0;
    uint64_t cross_trade_message = 0;
    uint64_t trade_cancel_message = 0;
    uint64_t cross_correction_message = 0;
    uint64_t retail_price_improvement_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        nyse::arcaequities::integratedfeed::pillar::v2_5_g::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    nyse::arcaequities::integratedfeed::pillar::v2_5_g::seq_action on_transport_header(const nyse::arcaequities::integratedfeed::pillar::v2_5_g::packet_header& transport, const packet::Frame&) {
        if (transport.delivery_flag.get().value() == nyse::arcaequities::integratedfeed::pillar::v2_5_g::delivery_flag::enum_type::heartbeat) {
            ++heartbeats;
            return nyse::arcaequities::integratedfeed::pillar::v2_5_g::seq_action::skip;
        }

        total_messages += transport.number_msgs.get().value();

        return nyse::arcaequities::integratedfeed::pillar::v2_5_g::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const nyse::arcaequities::integratedfeed::pillar::v2_5_g::sequence_number_reset_message&, std::uint64_t, const nyse::arcaequities::integratedfeed::pillar::v2_5_g::packet_header&)
        { ++sequence_number_reset_message; ++matched_messages; }
    void on_message(const nyse::arcaequities::integratedfeed::pillar::v2_5_g::source_time_reference_message&, std::uint64_t, const nyse::arcaequities::integratedfeed::pillar::v2_5_g::packet_header&)
        { ++source_time_reference_message; ++matched_messages; }
    void on_message(const nyse::arcaequities::integratedfeed::pillar::v2_5_g::symbol_index_mapping_message&, std::uint64_t, const nyse::arcaequities::integratedfeed::pillar::v2_5_g::packet_header&)
        { ++symbol_index_mapping_message; ++matched_messages; }
    void on_message(const nyse::arcaequities::integratedfeed::pillar::v2_5_g::symbol_clear_message&, std::uint64_t, const nyse::arcaequities::integratedfeed::pillar::v2_5_g::packet_header&)
        { ++symbol_clear_message; ++matched_messages; }
    void on_message(const nyse::arcaequities::integratedfeed::pillar::v2_5_g::security_status_message&, std::uint64_t, const nyse::arcaequities::integratedfeed::pillar::v2_5_g::packet_header&)
        { ++security_status_message; ++matched_messages; }
    void on_message(const nyse::arcaequities::integratedfeed::pillar::v2_5_g::add_order_message&, std::uint64_t, const nyse::arcaequities::integratedfeed::pillar::v2_5_g::packet_header&)
        { ++add_order_message; ++matched_messages; }
    void on_message(const nyse::arcaequities::integratedfeed::pillar::v2_5_g::modify_order_message&, std::uint64_t, const nyse::arcaequities::integratedfeed::pillar::v2_5_g::packet_header&)
        { ++modify_order_message; ++matched_messages; }
    void on_message(const nyse::arcaequities::integratedfeed::pillar::v2_5_g::delete_order_message&, std::uint64_t, const nyse::arcaequities::integratedfeed::pillar::v2_5_g::packet_header&)
        { ++delete_order_message; ++matched_messages; }
    void on_message(const nyse::arcaequities::integratedfeed::pillar::v2_5_g::order_execution_message&, std::uint64_t, const nyse::arcaequities::integratedfeed::pillar::v2_5_g::packet_header&)
        { ++order_execution_message; ++matched_messages; }
    void on_message(const nyse::arcaequities::integratedfeed::pillar::v2_5_g::replace_order_message&, std::uint64_t, const nyse::arcaequities::integratedfeed::pillar::v2_5_g::packet_header&)
        { ++replace_order_message; ++matched_messages; }
    void on_message(const nyse::arcaequities::integratedfeed::pillar::v2_5_g::imbalance_message&, std::uint64_t, const nyse::arcaequities::integratedfeed::pillar::v2_5_g::packet_header&)
        { ++imbalance_message; ++matched_messages; }
    void on_message(const nyse::arcaequities::integratedfeed::pillar::v2_5_g::add_order_refresh_message&, std::uint64_t, const nyse::arcaequities::integratedfeed::pillar::v2_5_g::packet_header&)
        { ++add_order_refresh_message; ++matched_messages; }
    void on_message(const nyse::arcaequities::integratedfeed::pillar::v2_5_g::non_displayed_trade_message&, std::uint64_t, const nyse::arcaequities::integratedfeed::pillar::v2_5_g::packet_header&)
        { ++non_displayed_trade_message; ++matched_messages; }
    void on_message(const nyse::arcaequities::integratedfeed::pillar::v2_5_g::cross_trade_message&, std::uint64_t, const nyse::arcaequities::integratedfeed::pillar::v2_5_g::packet_header&)
        { ++cross_trade_message; ++matched_messages; }
    void on_message(const nyse::arcaequities::integratedfeed::pillar::v2_5_g::trade_cancel_message&, std::uint64_t, const nyse::arcaequities::integratedfeed::pillar::v2_5_g::packet_header&)
        { ++trade_cancel_message; ++matched_messages; }
    void on_message(const nyse::arcaequities::integratedfeed::pillar::v2_5_g::cross_correction_message&, std::uint64_t, const nyse::arcaequities::integratedfeed::pillar::v2_5_g::packet_header&)
        { ++cross_correction_message; ++matched_messages; }
    void on_message(const nyse::arcaequities::integratedfeed::pillar::v2_5_g::retail_price_improvement_message&, std::uint64_t, const nyse::arcaequities::integratedfeed::pillar::v2_5_g::packet_header&)
        { ++retail_price_improvement_message; ++matched_messages; }

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
        std::cout << "  SequenceNumberResetMessage (1)       " << sequence_number_reset_message << std::endl;
        std::cout << "  SourceTimeReferenceMessage (2)       " << source_time_reference_message << std::endl;
        std::cout << "  SymbolIndexMappingMessage (3)        " << symbol_index_mapping_message << std::endl;
        std::cout << "  SymbolClearMessage (32)              " << symbol_clear_message << std::endl;
        std::cout << "  SecurityStatusMessage (34)           " << security_status_message << std::endl;
        std::cout << "  AddOrderMessage (100)                " << add_order_message << std::endl;
        std::cout << "  ModifyOrderMessage (101)             " << modify_order_message << std::endl;
        std::cout << "  DeleteOrderMessage (102)             " << delete_order_message << std::endl;
        std::cout << "  OrderExecutionMessage (103)          " << order_execution_message << std::endl;
        std::cout << "  ReplaceOrderMessage (104)            " << replace_order_message << std::endl;
        std::cout << "  ImbalanceMessage (105)               " << imbalance_message << std::endl;
        std::cout << "  AddOrderRefreshMessage (106)         " << add_order_refresh_message << std::endl;
        std::cout << "  NonDisplayedTradeMessage (110)       " << non_displayed_trade_message << std::endl;
        std::cout << "  CrossTradeMessage (111)              " << cross_trade_message << std::endl;
        std::cout << "  TradeCancelMessage (112)             " << trade_cancel_message << std::endl;
        std::cout << "  CrossCorrectionMessage (113)         " << cross_correction_message << std::endl;
        std::cout << "  RetailPriceImprovementMessage (114)  " << retail_price_improvement_message << std::endl;
    }
};
}
