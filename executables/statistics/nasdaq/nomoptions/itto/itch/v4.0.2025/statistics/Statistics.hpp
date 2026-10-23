#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/advanced/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/session.hpp"

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
    uint64_t system_event_message = 0;
    uint64_t options_directory_message = 0;
    uint64_t trading_action_message = 0;
    uint64_t security_open_message = 0;
    uint64_t add_order_message_short_message_form = 0;
    uint64_t add_order_message_long_form_message = 0;
    uint64_t add_quote_message_short_form_message = 0;
    uint64_t add_quote_message_long_form_message = 0;
    uint64_t single_side_executed_message = 0;
    uint64_t single_side_executed_with_price_message = 0;
    uint64_t order_cancel_message = 0;
    uint64_t single_side_replace_message_short_form = 0;
    uint64_t single_side_replace_message_long_form = 0;
    uint64_t single_side_delete_message = 0;
    uint64_t single_side_change_message = 0;
    uint64_t quote_replace_message_short_form = 0;
    uint64_t quote_replace_message_long_form = 0;
    uint64_t quote_delete_message = 0;
    uint64_t options_trade_messages_non_auction = 0;
    uint64_t options_cross_trade_message = 0;
    uint64_t broken_trade_order_executed_message = 0;
    uint64_t noii_message = 0;
    uint64_t end_of_replay_sequence_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        nasdaq::nomoptions::itto::itch::v4_0_2025::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    nasdaq::nomoptions::itto::itch::v4_0_2025::seq_action on_transport_header(const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header& transport, const packet::Frame&) {
        if (transport.message_count.get().value() == 0) {
            ++heartbeats;
            return nasdaq::nomoptions::itto::itch::v4_0_2025::seq_action::skip;
        }

        if (transport.message_count.get().value() == 65535) {
            ++heartbeats;
            return nasdaq::nomoptions::itto::itch::v4_0_2025::seq_action::skip;
        }

        total_messages += transport.message_count.get().value();

        return nasdaq::nomoptions::itto::itch::v4_0_2025::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::debug_packet&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++debug_packet; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::login_request_packet&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++login_request_packet; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::unsequenced_data_packet&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++unsequenced_data_packet; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::login_accepted_packet&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++login_accepted_packet; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::login_rejected_packet&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++login_rejected_packet; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::sequenced_data_packet&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++sequenced_data_packet; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::system_event_message&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++system_event_message; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::options_directory_message&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++options_directory_message; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::trading_action_message&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++trading_action_message; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::security_open_message&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++security_open_message; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::add_order_message_short_message_form&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++add_order_message_short_message_form; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::add_order_message_long_form_message&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++add_order_message_long_form_message; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::add_quote_message_short_form_message&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++add_quote_message_short_form_message; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::add_quote_message_long_form_message&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++add_quote_message_long_form_message; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::single_side_executed_message&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++single_side_executed_message; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::single_side_executed_with_price_message&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++single_side_executed_with_price_message; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::order_cancel_message&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++order_cancel_message; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::single_side_replace_message_short_form&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++single_side_replace_message_short_form; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::single_side_replace_message_long_form&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++single_side_replace_message_long_form; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::single_side_delete_message&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++single_side_delete_message; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::single_side_change_message&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++single_side_change_message; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::quote_replace_message_short_form&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++quote_replace_message_short_form; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::quote_replace_message_long_form&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++quote_replace_message_long_form; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::quote_delete_message&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++quote_delete_message; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::options_trade_messages_non_auction&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++options_trade_messages_non_auction; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::options_cross_trade_message&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++options_cross_trade_message; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::broken_trade_order_executed_message&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++broken_trade_order_executed_message; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::noii_message&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
        { ++noii_message; ++matched_messages; }
    void on_message(const nasdaq::nomoptions::itto::itch::v4_0_2025::end_of_replay_sequence_message&, std::uint64_t, const nasdaq::nomoptions::itto::itch::v4_0_2025::packet_header&)
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
        std::cout << "  DebugPacket                             " << debug_packet << std::endl;
        std::cout << "  LoginRequestPacket                      " << login_request_packet << std::endl;
        std::cout << "  UnsequencedDataPacket                   " << unsequenced_data_packet << std::endl;
        std::cout << "  LoginAcceptedPacket                     " << login_accepted_packet << std::endl;
        std::cout << "  LoginRejectedPacket                     " << login_rejected_packet << std::endl;
        std::cout << "  SequencedDataPacket                     " << sequenced_data_packet << std::endl;
        std::cout << "  SystemEventMessage (S)                  " << system_event_message << std::endl;
        std::cout << "  OptionsDirectoryMessage (R)             " << options_directory_message << std::endl;
        std::cout << "  TradingActionMessage (H)                " << trading_action_message << std::endl;
        std::cout << "  SecurityOpenMessage (O)                 " << security_open_message << std::endl;
        std::cout << "  AddOrderMessageShortMessageForm (a)     " << add_order_message_short_message_form << std::endl;
        std::cout << "  AddOrderMessageLongFormMessage (A)      " << add_order_message_long_form_message << std::endl;
        std::cout << "  AddQuoteMessageShortFormMessage (j)     " << add_quote_message_short_form_message << std::endl;
        std::cout << "  AddQuoteMessageLongFormMessage (J)      " << add_quote_message_long_form_message << std::endl;
        std::cout << "  SingleSideExecutedMessage (E)           " << single_side_executed_message << std::endl;
        std::cout << "  SingleSideExecutedWithPriceMessage (C)  " << single_side_executed_with_price_message << std::endl;
        std::cout << "  OrderCancelMessage (X)                  " << order_cancel_message << std::endl;
        std::cout << "  SingleSideReplaceMessageShortForm (u)   " << single_side_replace_message_short_form << std::endl;
        std::cout << "  SingleSideReplaceMessageLongForm (U)    " << single_side_replace_message_long_form << std::endl;
        std::cout << "  SingleSideDeleteMessage (D)             " << single_side_delete_message << std::endl;
        std::cout << "  SingleSideChangeMessage (G)             " << single_side_change_message << std::endl;
        std::cout << "  QuoteReplaceMessageShortForm (k)        " << quote_replace_message_short_form << std::endl;
        std::cout << "  QuoteReplaceMessageLongForm (K)         " << quote_replace_message_long_form << std::endl;
        std::cout << "  QuoteDeleteMessage (Y)                  " << quote_delete_message << std::endl;
        std::cout << "  OptionsTradeMessagesNonAuction (P)      " << options_trade_messages_non_auction << std::endl;
        std::cout << "  OptionsCrossTradeMessage (Q)            " << options_cross_trade_message << std::endl;
        std::cout << "  BrokenTradeOrderExecutedMessage (B)     " << broken_trade_order_executed_message << std::endl;
        std::cout << "  NoiiMessage (I)                         " << noii_message << std::endl;
        std::cout << "  EndOfReplaySequenceMessage (M)          " << end_of_replay_sequence_message << std::endl;
    }
};
}
