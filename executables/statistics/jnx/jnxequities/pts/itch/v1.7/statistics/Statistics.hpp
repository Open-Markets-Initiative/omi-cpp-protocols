#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/advanced/jnx/jnxequities/pts/itch/v1.7/messages/session.hpp"

namespace statistics {

// Jnx Itch C++ statistics
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
    uint64_t debug_packet = 0;
    uint64_t login_request_packet = 0;
    uint64_t unsequenced_data_packet = 0;
    uint64_t login_accepted_packet = 0;
    uint64_t login_rejected_packet = 0;
    uint64_t sequenced_data_packet = 0;
    uint64_t seconds_message = 0;
    uint64_t system_event_message = 0;
    uint64_t price_tick_size_message = 0;
    uint64_t orderbook_directory_message = 0;
    uint64_t trading_state_message = 0;
    uint64_t short_selling_price_restriction_state_message = 0;
    uint64_t order_added_without_attributes_message = 0;
    uint64_t order_added_with_attributes_message = 0;
    uint64_t order_executed_message = 0;
    uint64_t order_deleted_message = 0;
    uint64_t order_replaced_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        jnx::jnxequities::pts::itch::v1_7::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    jnx::jnxequities::pts::itch::v1_7::seq_action on_transport_header(const jnx::jnxequities::pts::itch::v1_7::packet_header& transport, const packet::Frame&) {
        if (transport.message_count.get().value() == 0) {
            ++heartbeats;
            return jnx::jnxequities::pts::itch::v1_7::seq_action::skip;
        }

        if (transport.message_count.get().value() == 65535) {
            ++heartbeats;
            return jnx::jnxequities::pts::itch::v1_7::seq_action::skip;
        }

        total_messages += transport.message_count.get().value();

        return jnx::jnxequities::pts::itch::v1_7::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const jnx::jnxequities::pts::itch::v1_7::debug_packet&, std::uint64_t, const jnx::jnxequities::pts::itch::v1_7::packet_header&)
        { ++debug_packet; ++matched_messages; }
    void on_message(const jnx::jnxequities::pts::itch::v1_7::login_request_packet&, std::uint64_t, const jnx::jnxequities::pts::itch::v1_7::packet_header&)
        { ++login_request_packet; ++matched_messages; }
    void on_message(const jnx::jnxequities::pts::itch::v1_7::unsequenced_data_packet&, std::uint64_t, const jnx::jnxequities::pts::itch::v1_7::packet_header&)
        { ++unsequenced_data_packet; ++matched_messages; }
    void on_message(const jnx::jnxequities::pts::itch::v1_7::login_accepted_packet&, std::uint64_t, const jnx::jnxequities::pts::itch::v1_7::packet_header&)
        { ++login_accepted_packet; ++matched_messages; }
    void on_message(const jnx::jnxequities::pts::itch::v1_7::login_rejected_packet&, std::uint64_t, const jnx::jnxequities::pts::itch::v1_7::packet_header&)
        { ++login_rejected_packet; ++matched_messages; }
    void on_message(const jnx::jnxequities::pts::itch::v1_7::sequenced_data_packet&, std::uint64_t, const jnx::jnxequities::pts::itch::v1_7::packet_header&)
        { ++sequenced_data_packet; ++matched_messages; }
    void on_message(const jnx::jnxequities::pts::itch::v1_7::seconds_message&, std::uint64_t, const jnx::jnxequities::pts::itch::v1_7::packet_header&)
        { ++seconds_message; ++matched_messages; }
    void on_message(const jnx::jnxequities::pts::itch::v1_7::system_event_message&, std::uint64_t, const jnx::jnxequities::pts::itch::v1_7::packet_header&)
        { ++system_event_message; ++matched_messages; }
    void on_message(const jnx::jnxequities::pts::itch::v1_7::price_tick_size_message&, std::uint64_t, const jnx::jnxequities::pts::itch::v1_7::packet_header&)
        { ++price_tick_size_message; ++matched_messages; }
    void on_message(const jnx::jnxequities::pts::itch::v1_7::orderbook_directory_message&, std::uint64_t, const jnx::jnxequities::pts::itch::v1_7::packet_header&)
        { ++orderbook_directory_message; ++matched_messages; }
    void on_message(const jnx::jnxequities::pts::itch::v1_7::trading_state_message&, std::uint64_t, const jnx::jnxequities::pts::itch::v1_7::packet_header&)
        { ++trading_state_message; ++matched_messages; }
    void on_message(const jnx::jnxequities::pts::itch::v1_7::short_selling_price_restriction_state_message&, std::uint64_t, const jnx::jnxequities::pts::itch::v1_7::packet_header&)
        { ++short_selling_price_restriction_state_message; ++matched_messages; }
    void on_message(const jnx::jnxequities::pts::itch::v1_7::order_added_without_attributes_message&, std::uint64_t, const jnx::jnxequities::pts::itch::v1_7::packet_header&)
        { ++order_added_without_attributes_message; ++matched_messages; }
    void on_message(const jnx::jnxequities::pts::itch::v1_7::order_added_with_attributes_message&, std::uint64_t, const jnx::jnxequities::pts::itch::v1_7::packet_header&)
        { ++order_added_with_attributes_message; ++matched_messages; }
    void on_message(const jnx::jnxequities::pts::itch::v1_7::order_executed_message&, std::uint64_t, const jnx::jnxequities::pts::itch::v1_7::packet_header&)
        { ++order_executed_message; ++matched_messages; }
    void on_message(const jnx::jnxequities::pts::itch::v1_7::order_deleted_message&, std::uint64_t, const jnx::jnxequities::pts::itch::v1_7::packet_header&)
        { ++order_deleted_message; ++matched_messages; }
    void on_message(const jnx::jnxequities::pts::itch::v1_7::order_replaced_message&, std::uint64_t, const jnx::jnxequities::pts::itch::v1_7::packet_header&)
        { ++order_replaced_message; ++matched_messages; }

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
        std::cout << "  DebugPacket                                   " << debug_packet << std::endl;
        std::cout << "  LoginRequestPacket                            " << login_request_packet << std::endl;
        std::cout << "  UnsequencedDataPacket                         " << unsequenced_data_packet << std::endl;
        std::cout << "  LoginAcceptedPacket                           " << login_accepted_packet << std::endl;
        std::cout << "  LoginRejectedPacket                           " << login_rejected_packet << std::endl;
        std::cout << "  SequencedDataPacket                           " << sequenced_data_packet << std::endl;
        std::cout << "  SecondsMessage (T)                            " << seconds_message << std::endl;
        std::cout << "  SystemEventMessage (S)                        " << system_event_message << std::endl;
        std::cout << "  PriceTickSizeMessage (L)                      " << price_tick_size_message << std::endl;
        std::cout << "  OrderbookDirectoryMessage (R)                 " << orderbook_directory_message << std::endl;
        std::cout << "  TradingStateMessage (H)                       " << trading_state_message << std::endl;
        std::cout << "  ShortSellingPriceRestrictionStateMessage (Y)  " << short_selling_price_restriction_state_message << std::endl;
        std::cout << "  OrderAddedWithoutAttributesMessage (A)        " << order_added_without_attributes_message << std::endl;
        std::cout << "  OrderAddedWithAttributesMessage (F)           " << order_added_with_attributes_message << std::endl;
        std::cout << "  OrderExecutedMessage (E)                      " << order_executed_message << std::endl;
        std::cout << "  OrderDeletedMessage (D)                       " << order_deleted_message << std::endl;
        std::cout << "  OrderReplacedMessage (U)                      " << order_replaced_message << std::endl;
    }
};
}
