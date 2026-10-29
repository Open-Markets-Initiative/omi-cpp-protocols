#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/advanced/nyse/arcaoptions/topfeed/pillar/v1.2.c/messages/session.hpp"

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
    uint64_t time_reference_message = 0;
    uint64_t symbol_index_mapping_message = 0;
    uint64_t retransmission_request_message = 0;
    uint64_t request_response_message = 0;
    uint64_t heartbeat_response_message = 0;
    uint64_t symbol_index_mapping_request_message = 0;
    uint64_t refresh_request_message = 0;
    uint64_t message_unavailable_message = 0;
    uint64_t symbol_clear_message = 0;
    uint64_t security_status_message = 0;
    uint64_t refresh_header_message = 0;
    uint64_t outright_series_index_mapping_message = 0;
    uint64_t options_status_message = 0;
    uint64_t options_quote_message = 0;
    uint64_t options_trade_message = 0;
    uint64_t options_trade_cancel_message = 0;
    uint64_t options_trade_correction_message = 0;
    uint64_t options_imbalance_message = 0;
    uint64_t series_rfq_message = 0;
    uint64_t outright_series_summary_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        nyse::arcaoptions::topfeed::pillar::v1_2_c::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    nyse::arcaoptions::topfeed::pillar::v1_2_c::seq_action on_transport_header(const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header& transport, const packet::Frame&) {
        if (transport.delivery_flag.get().value() == nyse::arcaoptions::topfeed::pillar::v1_2_c::delivery_flag::enum_type::heartbeat) {
            ++heartbeats;
            return nyse::arcaoptions::topfeed::pillar::v1_2_c::seq_action::skip;
        }

        total_messages += transport.number_msgs.get().value();

        return nyse::arcaoptions::topfeed::pillar::v1_2_c::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::sequence_number_reset_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++sequence_number_reset_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::time_reference_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++time_reference_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::symbol_index_mapping_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++symbol_index_mapping_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::retransmission_request_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++retransmission_request_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::request_response_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++request_response_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::heartbeat_response_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++heartbeat_response_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::symbol_index_mapping_request_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++symbol_index_mapping_request_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::refresh_request_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++refresh_request_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::message_unavailable_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++message_unavailable_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::symbol_clear_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++symbol_clear_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::security_status_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++security_status_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::refresh_header_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++refresh_header_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::outright_series_index_mapping_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++outright_series_index_mapping_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::options_status_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++options_status_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::options_quote_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++options_quote_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::options_trade_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++options_trade_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::options_trade_cancel_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++options_trade_cancel_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::options_trade_correction_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++options_trade_correction_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::options_imbalance_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++options_imbalance_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::series_rfq_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++series_rfq_message; ++matched_messages; }
    void on_message(const nyse::arcaoptions::topfeed::pillar::v1_2_c::outright_series_summary_message&, std::uint64_t, const nyse::arcaoptions::topfeed::pillar::v1_2_c::packet_header&)
        { ++outright_series_summary_message; ++matched_messages; }

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
        std::cout << "  SequenceNumberResetMessage (1)          " << sequence_number_reset_message << std::endl;
        std::cout << "  TimeReferenceMessage (2)                " << time_reference_message << std::endl;
        std::cout << "  SymbolIndexMappingMessage (3)           " << symbol_index_mapping_message << std::endl;
        std::cout << "  RetransmissionRequestMessage (10)       " << retransmission_request_message << std::endl;
        std::cout << "  RequestResponseMessage (11)             " << request_response_message << std::endl;
        std::cout << "  HeartbeatResponseMessage (12)           " << heartbeat_response_message << std::endl;
        std::cout << "  SymbolIndexMappingRequestMessage (13)   " << symbol_index_mapping_request_message << std::endl;
        std::cout << "  RefreshRequestMessage (15)              " << refresh_request_message << std::endl;
        std::cout << "  MessageUnavailableMessage (31)          " << message_unavailable_message << std::endl;
        std::cout << "  SymbolClearMessage (32)                 " << symbol_clear_message << std::endl;
        std::cout << "  SecurityStatusMessage (34)              " << security_status_message << std::endl;
        std::cout << "  RefreshHeaderMessage (35)               " << refresh_header_message << std::endl;
        std::cout << "  OutrightSeriesIndexMappingMessage (50)  " << outright_series_index_mapping_message << std::endl;
        std::cout << "  OptionsStatusMessage (51)               " << options_status_message << std::endl;
        std::cout << "  OptionsQuoteMessage (340)               " << options_quote_message << std::endl;
        std::cout << "  OptionsTradeMessage (320)               " << options_trade_message << std::endl;
        std::cout << "  OptionsTradeCancelMessage (321)         " << options_trade_cancel_message << std::endl;
        std::cout << "  OptionsTradeCorrectionMessage (322)     " << options_trade_correction_message << std::endl;
        std::cout << "  OptionsImbalanceMessage (305)           " << options_imbalance_message << std::endl;
        std::cout << "  SeriesRfqMessage (307)                  " << series_rfq_message << std::endl;
        std::cout << "  OutrightSeriesSummaryMessage (323)      " << outright_series_summary_message << std::endl;
    }
};
}
