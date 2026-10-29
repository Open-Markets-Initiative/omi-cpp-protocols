#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/advanced/cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/messages/session.hpp"

namespace statistics {

// Cboe Pitch C++ statistics
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
    uint64_t time_message = 0;
    uint64_t unit_clear_message = 0;
    uint64_t add_order_long_message = 0;
    uint64_t add_order_short_message = 0;
    uint64_t add_order_expanded_message = 0;
    uint64_t order_executed_message = 0;
    uint64_t order_executed_at_price_size_message = 0;
    uint64_t reduce_size_long_message = 0;
    uint64_t reduce_size_short_message = 0;
    uint64_t modify_order_long_message = 0;
    uint64_t modify_order_short_message = 0;
    uint64_t delete_order_message = 0;
    uint64_t trade_long_message = 0;
    uint64_t trade_short_message = 0;
    uint64_t trade_expanded_message = 0;
    uint64_t trade_break_message = 0;
    uint64_t end_of_session_message = 0;
    uint64_t symbol_mapping_message = 0;
    uint64_t trading_status_message = 0;
    uint64_t auction_update_message = 0;
    uint64_t auction_summary_message = 0;
    uint64_t retail_price_improvement_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::seq_action on_transport_header(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header& transport, const packet::Frame&) {
        if (transport.message_count.get().value() == 0) {
            ++heartbeats;
            return cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::seq_action::skip;
        }

        total_messages += transport.message_count.get().value();

        return cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::time_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++time_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::unit_clear_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++unit_clear_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::add_order_long_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++add_order_long_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::add_order_short_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++add_order_short_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::add_order_expanded_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++add_order_expanded_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::order_executed_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++order_executed_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::order_executed_at_price_size_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++order_executed_at_price_size_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::reduce_size_long_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++reduce_size_long_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::reduce_size_short_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++reduce_size_short_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::modify_order_long_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++modify_order_long_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::modify_order_short_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++modify_order_short_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::delete_order_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++delete_order_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::trade_long_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++trade_long_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::trade_short_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++trade_short_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::trade_expanded_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++trade_expanded_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::trade_break_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++trade_break_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::end_of_session_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++end_of_session_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::symbol_mapping_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++symbol_mapping_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::trading_status_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++trading_status_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::auction_update_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++auction_update_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::auction_summary_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
        { ++auction_summary_message; ++matched_messages; }
    void on_message(const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::retail_price_improvement_message&, std::uint64_t, const cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4::packet_header&)
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
        std::cout << "  TimeMessage (0x20)                      " << time_message << std::endl;
        std::cout << "  UnitClearMessage (0x97)                 " << unit_clear_message << std::endl;
        std::cout << "  AddOrderLongMessage (0x21)              " << add_order_long_message << std::endl;
        std::cout << "  AddOrderShortMessage (0x22)             " << add_order_short_message << std::endl;
        std::cout << "  AddOrderExpandedMessage (0x2F)          " << add_order_expanded_message << std::endl;
        std::cout << "  OrderExecutedMessage (0x23)             " << order_executed_message << std::endl;
        std::cout << "  OrderExecutedAtPriceSizeMessage (0x24)  " << order_executed_at_price_size_message << std::endl;
        std::cout << "  ReduceSizeLongMessage (0x25)            " << reduce_size_long_message << std::endl;
        std::cout << "  ReduceSizeShortMessage (0x26)           " << reduce_size_short_message << std::endl;
        std::cout << "  ModifyOrderLongMessage (0x27)           " << modify_order_long_message << std::endl;
        std::cout << "  ModifyOrderShortMessage (0x28)          " << modify_order_short_message << std::endl;
        std::cout << "  DeleteOrderMessage (0x29)               " << delete_order_message << std::endl;
        std::cout << "  TradeLongMessage (0x2A)                 " << trade_long_message << std::endl;
        std::cout << "  TradeShortMessage (0x2B)                " << trade_short_message << std::endl;
        std::cout << "  TradeExpandedMessage (0x30)             " << trade_expanded_message << std::endl;
        std::cout << "  TradeBreakMessage (0x2C)                " << trade_break_message << std::endl;
        std::cout << "  EndOfSessionMessage (0x2D)              " << end_of_session_message << std::endl;
        std::cout << "  SymbolMappingMessage (0x2E)             " << symbol_mapping_message << std::endl;
        std::cout << "  TradingStatusMessage (0x31)             " << trading_status_message << std::endl;
        std::cout << "  AuctionUpdateMessage (0x95)             " << auction_update_message << std::endl;
        std::cout << "  AuctionSummaryMessage (0x96)            " << auction_summary_message << std::endl;
        std::cout << "  RetailPriceImprovementMessage (0x98)    " << retail_price_improvement_message << std::endl;
    }
};
}
