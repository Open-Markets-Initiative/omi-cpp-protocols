#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/advanced/nasdaq/nordicequities/totalview/itch/v3.04.x/messages/session.hpp"

namespace statistics {

// Nasdaq Itch C++ statistics
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
    uint64_t system_event_message = 0;
    uint64_t order_book_trading_action_message = 0;
    uint64_t order_book_directory_message = 0;
    uint64_t add_order_message = 0;
    uint64_t add_order_mpid_attribution_message = 0;
    uint64_t order_executed_message = 0;
    uint64_t order_executed_with_price_message = 0;
    uint64_t order_cancel_message = 0;
    uint64_t order_delete_message = 0;
    uint64_t order_book_flush_message = 0;
    uint64_t order_replace_message = 0;
    uint64_t trade_message = 0;
    uint64_t cross_trade_message = 0;
    uint64_t broken_trade_message = 0;
    uint64_t noii_message = 0;
    uint64_t moii_message = 0;
    uint64_t execution_summary_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        nasdaq::nordicequities::totalview::itch::v3_04_x::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    nasdaq::nordicequities::totalview::itch::v3_04_x::seq_action on_transport_header(const nasdaq::nordicequities::totalview::itch::v3_04_x::packet_header& transport, const packet::Frame&) {
        if (transport.message_count.get().value() == 0) {
            ++heartbeats;
            return nasdaq::nordicequities::totalview::itch::v3_04_x::seq_action::skip;
        }

        if (transport.message_count.get().value() == 65535) {
            ++heartbeats;
            return nasdaq::nordicequities::totalview::itch::v3_04_x::seq_action::skip;
        }

        total_messages += transport.message_count.get().value();

        return nasdaq::nordicequities::totalview::itch::v3_04_x::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const nasdaq::nordicequities::totalview::itch::v3_04_x::system_event_message&, std::uint64_t, const nasdaq::nordicequities::totalview::itch::v3_04_x::packet_header&)
        { ++system_event_message; ++matched_messages; }
    void on_message(const nasdaq::nordicequities::totalview::itch::v3_04_x::order_book_trading_action_message&, std::uint64_t, const nasdaq::nordicequities::totalview::itch::v3_04_x::packet_header&)
        { ++order_book_trading_action_message; ++matched_messages; }
    void on_message(const nasdaq::nordicequities::totalview::itch::v3_04_x::order_book_directory_message&, std::uint64_t, const nasdaq::nordicequities::totalview::itch::v3_04_x::packet_header&)
        { ++order_book_directory_message; ++matched_messages; }
    void on_message(const nasdaq::nordicequities::totalview::itch::v3_04_x::add_order_message&, std::uint64_t, const nasdaq::nordicequities::totalview::itch::v3_04_x::packet_header&)
        { ++add_order_message; ++matched_messages; }
    void on_message(const nasdaq::nordicequities::totalview::itch::v3_04_x::add_order_mpid_attribution_message&, std::uint64_t, const nasdaq::nordicequities::totalview::itch::v3_04_x::packet_header&)
        { ++add_order_mpid_attribution_message; ++matched_messages; }
    void on_message(const nasdaq::nordicequities::totalview::itch::v3_04_x::order_executed_message&, std::uint64_t, const nasdaq::nordicequities::totalview::itch::v3_04_x::packet_header&)
        { ++order_executed_message; ++matched_messages; }
    void on_message(const nasdaq::nordicequities::totalview::itch::v3_04_x::order_executed_with_price_message&, std::uint64_t, const nasdaq::nordicequities::totalview::itch::v3_04_x::packet_header&)
        { ++order_executed_with_price_message; ++matched_messages; }
    void on_message(const nasdaq::nordicequities::totalview::itch::v3_04_x::order_cancel_message&, std::uint64_t, const nasdaq::nordicequities::totalview::itch::v3_04_x::packet_header&)
        { ++order_cancel_message; ++matched_messages; }
    void on_message(const nasdaq::nordicequities::totalview::itch::v3_04_x::order_delete_message&, std::uint64_t, const nasdaq::nordicequities::totalview::itch::v3_04_x::packet_header&)
        { ++order_delete_message; ++matched_messages; }
    void on_message(const nasdaq::nordicequities::totalview::itch::v3_04_x::order_book_flush_message&, std::uint64_t, const nasdaq::nordicequities::totalview::itch::v3_04_x::packet_header&)
        { ++order_book_flush_message; ++matched_messages; }
    void on_message(const nasdaq::nordicequities::totalview::itch::v3_04_x::order_replace_message&, std::uint64_t, const nasdaq::nordicequities::totalview::itch::v3_04_x::packet_header&)
        { ++order_replace_message; ++matched_messages; }
    void on_message(const nasdaq::nordicequities::totalview::itch::v3_04_x::trade_message&, std::uint64_t, const nasdaq::nordicequities::totalview::itch::v3_04_x::packet_header&)
        { ++trade_message; ++matched_messages; }
    void on_message(const nasdaq::nordicequities::totalview::itch::v3_04_x::cross_trade_message&, std::uint64_t, const nasdaq::nordicequities::totalview::itch::v3_04_x::packet_header&)
        { ++cross_trade_message; ++matched_messages; }
    void on_message(const nasdaq::nordicequities::totalview::itch::v3_04_x::broken_trade_message&, std::uint64_t, const nasdaq::nordicequities::totalview::itch::v3_04_x::packet_header&)
        { ++broken_trade_message; ++matched_messages; }
    void on_message(const nasdaq::nordicequities::totalview::itch::v3_04_x::noii_message&, std::uint64_t, const nasdaq::nordicequities::totalview::itch::v3_04_x::packet_header&)
        { ++noii_message; ++matched_messages; }
    void on_message(const nasdaq::nordicequities::totalview::itch::v3_04_x::moii_message&, std::uint64_t, const nasdaq::nordicequities::totalview::itch::v3_04_x::packet_header&)
        { ++moii_message; ++matched_messages; }
    void on_message(const nasdaq::nordicequities::totalview::itch::v3_04_x::execution_summary_message&, std::uint64_t, const nasdaq::nordicequities::totalview::itch::v3_04_x::packet_header&)
        { ++execution_summary_message; ++matched_messages; }

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
        std::cout << "  SystemEventMessage (S)              " << system_event_message << std::endl;
        std::cout << "  OrderBookTradingActionMessage (H)   " << order_book_trading_action_message << std::endl;
        std::cout << "  OrderBookDirectoryMessage (R)       " << order_book_directory_message << std::endl;
        std::cout << "  AddOrderMessage (A)                 " << add_order_message << std::endl;
        std::cout << "  AddOrderMpidAttributionMessage (F)  " << add_order_mpid_attribution_message << std::endl;
        std::cout << "  OrderExecutedMessage (E)            " << order_executed_message << std::endl;
        std::cout << "  OrderExecutedWithPriceMessage (C)   " << order_executed_with_price_message << std::endl;
        std::cout << "  OrderCancelMessage (X)              " << order_cancel_message << std::endl;
        std::cout << "  OrderDeleteMessage (D)              " << order_delete_message << std::endl;
        std::cout << "  OrderBookFlushMessage (Y)           " << order_book_flush_message << std::endl;
        std::cout << "  OrderReplaceMessage (U)             " << order_replace_message << std::endl;
        std::cout << "  TradeMessage (P)                    " << trade_message << std::endl;
        std::cout << "  CrossTradeMessage (Q)               " << cross_trade_message << std::endl;
        std::cout << "  BrokenTradeMessage (B)              " << broken_trade_message << std::endl;
        std::cout << "  NoiiMessage (I)                     " << noii_message << std::endl;
        std::cout << "  MoiiMessage (J)                     " << moii_message << std::endl;
        std::cout << "  ExecutionSummaryMessage (K)         " << execution_summary_message << std::endl;
    }
};
}
