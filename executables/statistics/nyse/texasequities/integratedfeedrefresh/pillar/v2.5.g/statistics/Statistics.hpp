#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/advanced/nyse/texasequities/integratedfeedrefresh/pillar/v2.5.g/messages/session.hpp"

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
    uint64_t security_status_message = 0;
    uint64_t refresh_header_message = 0;
    uint64_t imbalance_message = 0;
    uint64_t add_order_refresh_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::seq_action on_transport_header(const nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::packet_header& transport, const packet::Frame&) {
        if (transport.delivery_flag.get().value() == nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::delivery_flag::enum_type::heartbeat) {
            ++heartbeats;
            return nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::seq_action::skip;
        }

        total_messages += transport.number_msgs.get().value();

        return nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::sequence_number_reset_message&, std::uint64_t, const nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::packet_header&)
        { ++sequence_number_reset_message; ++matched_messages; }
    void on_message(const nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::source_time_reference_message&, std::uint64_t, const nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::packet_header&)
        { ++source_time_reference_message; ++matched_messages; }
    void on_message(const nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::symbol_index_mapping_message&, std::uint64_t, const nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::packet_header&)
        { ++symbol_index_mapping_message; ++matched_messages; }
    void on_message(const nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::security_status_message&, std::uint64_t, const nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::packet_header&)
        { ++security_status_message; ++matched_messages; }
    void on_message(const nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::refresh_header_message&, std::uint64_t, const nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::packet_header&)
        { ++refresh_header_message; ++matched_messages; }
    void on_message(const nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::imbalance_message&, std::uint64_t, const nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::packet_header&)
        { ++imbalance_message; ++matched_messages; }
    void on_message(const nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::add_order_refresh_message&, std::uint64_t, const nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g::packet_header&)
        { ++add_order_refresh_message; ++matched_messages; }

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
        std::cout << "  SequenceNumberResetMessage (1)  " << sequence_number_reset_message << std::endl;
        std::cout << "  SourceTimeReferenceMessage (2)  " << source_time_reference_message << std::endl;
        std::cout << "  SymbolIndexMappingMessage (3)   " << symbol_index_mapping_message << std::endl;
        std::cout << "  SecurityStatusMessage (34)      " << security_status_message << std::endl;
        std::cout << "  RefreshHeaderMessage (35)       " << refresh_header_message << std::endl;
        std::cout << "  ImbalanceMessage (105)          " << imbalance_message << std::endl;
        std::cout << "  AddOrderRefreshMessage (106)    " << add_order_refresh_message << std::endl;
    }
};
}
