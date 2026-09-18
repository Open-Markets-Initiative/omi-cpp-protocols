#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/advanced/iex/iexequities/tops/iextp/v1.56/messages/session.hpp"

namespace statistics {

// Iex IexTp C++ statistics
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
    uint64_t quote_update_message = 0;
    uint64_t trade_report_message = 0;
    uint64_t trade_break_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        iex::iexequities::tops::iextp::v1_56::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    iex::iexequities::tops::iextp::v1_56::seq_action on_transport_header(const iex::iexequities::tops::iextp::v1_56::iextp_header& transport, const packet::Frame&) {
        if (transport.message_count.get().value() == 0) {
            ++heartbeats;
            return iex::iexequities::tops::iextp::v1_56::seq_action::skip;
        }

        total_messages += transport.message_count.get().value();

        return iex::iexequities::tops::iextp::v1_56::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const iex::iexequities::tops::iextp::v1_56::quote_update_message&, std::uint64_t, const iex::iexequities::tops::iextp::v1_56::iextp_header&)
        { ++quote_update_message; ++matched_messages; }
    void on_message(const iex::iexequities::tops::iextp::v1_56::trade_report_message&, std::uint64_t, const iex::iexequities::tops::iextp::v1_56::iextp_header&)
        { ++trade_report_message; ++matched_messages; }
    void on_message(const iex::iexequities::tops::iextp::v1_56::trade_break_message&, std::uint64_t, const iex::iexequities::tops::iextp::v1_56::iextp_header&)
        { ++trade_break_message; ++matched_messages; }

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
        std::cout << "  QuoteUpdateMessage (Q)  " << quote_update_message << std::endl;
        std::cout << "  TradeReportMessage (T)  " << trade_report_message << std::endl;
        std::cout << "  TradeBreakMessage (B)   " << trade_break_message << std::endl;
    }
};
}
