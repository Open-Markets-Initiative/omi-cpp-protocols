#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/advanced/jpx/osederivatives/geniuminet/itch/v5.0.6/messages/session.hpp"

namespace statistics {

// Jpx Itch C++ statistics
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
    uint64_t seconds_message = 0;
    uint64_t order_book_directory = 0;
    uint64_t combination_orderbook_leg = 0;
    uint64_t tick_size_table_entry = 0;
    uint64_t system_event_message = 0;
    uint64_t order_book_state_message = 0;
    uint64_t add_order_no_mpid = 0;
    uint64_t add_order_with_mpid = 0;
    uint64_t order_executed_message = 0;
    uint64_t order_executed_with_price_message = 0;
    uint64_t order_replace_message = 0;
    uint64_t order_delete_message = 0;
    uint64_t trade_message = 0;
    uint64_t equilibrium_price_update = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        jpx::osederivatives::geniuminet::itch::v5_0_6::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    jpx::osederivatives::geniuminet::itch::v5_0_6::seq_action on_transport_header(const jpx::osederivatives::geniuminet::itch::v5_0_6::packet_header& transport, const packet::Frame&) {
        if (transport.message_count.get().value() == 0) {
            ++heartbeats;
            return jpx::osederivatives::geniuminet::itch::v5_0_6::seq_action::skip;
        }

        if (transport.message_count.get().value() == 65535) {
            ++heartbeats;
            return jpx::osederivatives::geniuminet::itch::v5_0_6::seq_action::skip;
        }

        total_messages += transport.message_count.get().value();

        return jpx::osederivatives::geniuminet::itch::v5_0_6::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const jpx::osederivatives::geniuminet::itch::v5_0_6::seconds_message&, std::uint64_t, const jpx::osederivatives::geniuminet::itch::v5_0_6::packet_header&)
        { ++seconds_message; ++matched_messages; }
    void on_message(const jpx::osederivatives::geniuminet::itch::v5_0_6::order_book_directory&, std::uint64_t, const jpx::osederivatives::geniuminet::itch::v5_0_6::packet_header&)
        { ++order_book_directory; ++matched_messages; }
    void on_message(const jpx::osederivatives::geniuminet::itch::v5_0_6::combination_orderbook_leg&, std::uint64_t, const jpx::osederivatives::geniuminet::itch::v5_0_6::packet_header&)
        { ++combination_orderbook_leg; ++matched_messages; }
    void on_message(const jpx::osederivatives::geniuminet::itch::v5_0_6::tick_size_table_entry&, std::uint64_t, const jpx::osederivatives::geniuminet::itch::v5_0_6::packet_header&)
        { ++tick_size_table_entry; ++matched_messages; }
    void on_message(const jpx::osederivatives::geniuminet::itch::v5_0_6::system_event_message&, std::uint64_t, const jpx::osederivatives::geniuminet::itch::v5_0_6::packet_header&)
        { ++system_event_message; ++matched_messages; }
    void on_message(const jpx::osederivatives::geniuminet::itch::v5_0_6::order_book_state_message&, std::uint64_t, const jpx::osederivatives::geniuminet::itch::v5_0_6::packet_header&)
        { ++order_book_state_message; ++matched_messages; }
    void on_message(const jpx::osederivatives::geniuminet::itch::v5_0_6::add_order_no_mpid&, std::uint64_t, const jpx::osederivatives::geniuminet::itch::v5_0_6::packet_header&)
        { ++add_order_no_mpid; ++matched_messages; }
    void on_message(const jpx::osederivatives::geniuminet::itch::v5_0_6::add_order_with_mpid&, std::uint64_t, const jpx::osederivatives::geniuminet::itch::v5_0_6::packet_header&)
        { ++add_order_with_mpid; ++matched_messages; }
    void on_message(const jpx::osederivatives::geniuminet::itch::v5_0_6::order_executed_message&, std::uint64_t, const jpx::osederivatives::geniuminet::itch::v5_0_6::packet_header&)
        { ++order_executed_message; ++matched_messages; }
    void on_message(const jpx::osederivatives::geniuminet::itch::v5_0_6::order_executed_with_price_message&, std::uint64_t, const jpx::osederivatives::geniuminet::itch::v5_0_6::packet_header&)
        { ++order_executed_with_price_message; ++matched_messages; }
    void on_message(const jpx::osederivatives::geniuminet::itch::v5_0_6::order_replace_message&, std::uint64_t, const jpx::osederivatives::geniuminet::itch::v5_0_6::packet_header&)
        { ++order_replace_message; ++matched_messages; }
    void on_message(const jpx::osederivatives::geniuminet::itch::v5_0_6::order_delete_message&, std::uint64_t, const jpx::osederivatives::geniuminet::itch::v5_0_6::packet_header&)
        { ++order_delete_message; ++matched_messages; }
    void on_message(const jpx::osederivatives::geniuminet::itch::v5_0_6::trade_message&, std::uint64_t, const jpx::osederivatives::geniuminet::itch::v5_0_6::packet_header&)
        { ++trade_message; ++matched_messages; }
    void on_message(const jpx::osederivatives::geniuminet::itch::v5_0_6::equilibrium_price_update&, std::uint64_t, const jpx::osederivatives::geniuminet::itch::v5_0_6::packet_header&)
        { ++equilibrium_price_update; ++matched_messages; }

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
        std::cout << "  SecondsMessage (T)                 " << seconds_message << std::endl;
        std::cout << "  OrderBookDirectory (R)             " << order_book_directory << std::endl;
        std::cout << "  CombinationOrderbookLeg (M)        " << combination_orderbook_leg << std::endl;
        std::cout << "  TickSizeTableEntry (L)             " << tick_size_table_entry << std::endl;
        std::cout << "  SystemEventMessage (S)             " << system_event_message << std::endl;
        std::cout << "  OrderBookStateMessage (O)          " << order_book_state_message << std::endl;
        std::cout << "  AddOrderNoMpid (A)                 " << add_order_no_mpid << std::endl;
        std::cout << "  AddOrderWithMpid (F)               " << add_order_with_mpid << std::endl;
        std::cout << "  OrderExecutedMessage (E)           " << order_executed_message << std::endl;
        std::cout << "  OrderExecutedWithPriceMessage (C)  " << order_executed_with_price_message << std::endl;
        std::cout << "  OrderReplaceMessage (U)            " << order_replace_message << std::endl;
        std::cout << "  OrderDeleteMessage (D)             " << order_delete_message << std::endl;
        std::cout << "  TradeMessage (P)                   " << trade_message << std::endl;
        std::cout << "  EquilibriumPriceUpdate (Z)         " << equilibrium_price_update << std::endl;
    }
};
}
