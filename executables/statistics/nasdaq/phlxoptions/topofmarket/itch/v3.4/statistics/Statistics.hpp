#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/advanced/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/session.hpp"

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
    uint64_t debug_packet = 0;
    uint64_t login_request_packet = 0;
    uint64_t unsequenced_data_packet = 0;
    uint64_t login_accepted_packet = 0;
    uint64_t login_rejected_packet = 0;
    uint64_t sequenced_data_packet = 0;
    uint64_t timestamp_message = 0;
    uint64_t system_event_message = 0;
    uint64_t options_directory_message = 0;
    uint64_t trading_action_message = 0;
    uint64_t security_open_closed_message = 0;
    uint64_t short_best_bid_and_ask_update_message = 0;
    uint64_t long_best_bid_and_ask_update_message = 0;
    uint64_t short_best_ask_update_message = 0;
    uint64_t short_best_bid_update_message = 0;
    uint64_t long_best_ask_update_message = 0;
    uint64_t long_best_bid_update_message = 0;
    uint64_t trade_report_message = 0;
    uint64_t broken_trade_report_message = 0;
    uint64_t end_of_replay_sequence_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        nasdaq::phlxoptions::topofmarket::itch::v3_4::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    nasdaq::phlxoptions::topofmarket::itch::v3_4::seq_action on_transport_header(const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header& transport, const packet::Frame&) {
        if (transport.message_count.get().value() == 0) {
            ++heartbeats;
            return nasdaq::phlxoptions::topofmarket::itch::v3_4::seq_action::skip;
        }

        if (transport.message_count.get().value() == 65535) {
            ++heartbeats;
            return nasdaq::phlxoptions::topofmarket::itch::v3_4::seq_action::skip;
        }

        total_messages += transport.message_count.get().value();

        return nasdaq::phlxoptions::topofmarket::itch::v3_4::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::debug_packet&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++debug_packet; ++matched_messages; }
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::login_request_packet&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++login_request_packet; ++matched_messages; }
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::unsequenced_data_packet&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++unsequenced_data_packet; ++matched_messages; }
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::login_accepted_packet&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++login_accepted_packet; ++matched_messages; }
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::login_rejected_packet&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++login_rejected_packet; ++matched_messages; }
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::sequenced_data_packet&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++sequenced_data_packet; ++matched_messages; }
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::timestamp_message&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++timestamp_message; ++matched_messages; }
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::system_event_message&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++system_event_message; ++matched_messages; }
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::options_directory_message&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++options_directory_message; ++matched_messages; }
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::trading_action_message&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++trading_action_message; ++matched_messages; }
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::security_open_closed_message&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++security_open_closed_message; ++matched_messages; }
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::short_best_bid_and_ask_update_message&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++short_best_bid_and_ask_update_message; ++matched_messages; }
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::long_best_bid_and_ask_update_message&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++long_best_bid_and_ask_update_message; ++matched_messages; }
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::short_best_ask_update_message&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++short_best_ask_update_message; ++matched_messages; }
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::short_best_bid_update_message&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++short_best_bid_update_message; ++matched_messages; }
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::long_best_ask_update_message&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++long_best_ask_update_message; ++matched_messages; }
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::long_best_bid_update_message&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++long_best_bid_update_message; ++matched_messages; }
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::trade_report_message&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++trade_report_message; ++matched_messages; }
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::broken_trade_report_message&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++broken_trade_report_message; ++matched_messages; }
    void on_message(const nasdaq::phlxoptions::topofmarket::itch::v3_4::end_of_replay_sequence_message&, std::uint64_t, const nasdaq::phlxoptions::topofmarket::itch::v3_4::packet_header&)
        { ++end_of_replay_sequence_message; ++matched_messages; }

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
        std::cout << "  DebugPacket                          " << debug_packet << std::endl;
        std::cout << "  LoginRequestPacket                   " << login_request_packet << std::endl;
        std::cout << "  UnsequencedDataPacket                " << unsequenced_data_packet << std::endl;
        std::cout << "  LoginAcceptedPacket                  " << login_accepted_packet << std::endl;
        std::cout << "  LoginRejectedPacket                  " << login_rejected_packet << std::endl;
        std::cout << "  SequencedDataPacket                  " << sequenced_data_packet << std::endl;
        std::cout << "  TimestampMessage (T)                 " << timestamp_message << std::endl;
        std::cout << "  SystemEventMessage (S)               " << system_event_message << std::endl;
        std::cout << "  OptionsDirectoryMessage (D)          " << options_directory_message << std::endl;
        std::cout << "  TradingActionMessage (H)             " << trading_action_message << std::endl;
        std::cout << "  SecurityOpenClosedMessage (O)        " << security_open_closed_message << std::endl;
        std::cout << "  ShortBestBidAndAskUpdateMessage (q)  " << short_best_bid_and_ask_update_message << std::endl;
        std::cout << "  LongBestBidAndAskUpdateMessage (Q)   " << long_best_bid_and_ask_update_message << std::endl;
        std::cout << "  ShortBestAskUpdateMessage (a)        " << short_best_ask_update_message << std::endl;
        std::cout << "  ShortBestBidUpdateMessage (b)        " << short_best_bid_update_message << std::endl;
        std::cout << "  LongBestAskUpdateMessage (A)         " << long_best_ask_update_message << std::endl;
        std::cout << "  LongBestBidUpdateMessage (B)         " << long_best_bid_update_message << std::endl;
        std::cout << "  TradeReportMessage (R)               " << trade_report_message << std::endl;
        std::cout << "  BrokenTradeReportMessage (X)         " << broken_trade_report_message << std::endl;
        std::cout << "  EndOfReplaySequenceMessage (M)       " << end_of_replay_sequence_message << std::endl;
    }
};
}
