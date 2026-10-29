#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/advanced/nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/messages/session.hpp"

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
    uint64_t complex_strategy_directory_message = 0;
    uint64_t strategy_open_closed_message = 0;
    uint64_t strategy_trading_action_message = 0;
    uint64_t strategy_best_bid_and_ask_update = 0;
    uint64_t strategy_best_bid_update = 0;
    uint64_t strategy_best_ask_update = 0;
    uint64_t complex_strategy_ticker_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::seq_action on_transport_header(const nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::packet_header& transport, const packet::Frame&) {
        if (transport.message_count.get().value() == 0) {
            ++heartbeats;
            return nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::seq_action::skip;
        }

        if (transport.message_count.get().value() == 65535) {
            ++heartbeats;
            return nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::seq_action::skip;
        }

        total_messages += transport.message_count.get().value();

        return nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::system_event_message&, std::uint64_t, const nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::packet_header&)
        { ++system_event_message; ++matched_messages; }
    void on_message(const nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::complex_strategy_directory_message&, std::uint64_t, const nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::packet_header&)
        { ++complex_strategy_directory_message; ++matched_messages; }
    void on_message(const nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::strategy_open_closed_message&, std::uint64_t, const nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::packet_header&)
        { ++strategy_open_closed_message; ++matched_messages; }
    void on_message(const nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::strategy_trading_action_message&, std::uint64_t, const nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::packet_header&)
        { ++strategy_trading_action_message; ++matched_messages; }
    void on_message(const nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::strategy_best_bid_and_ask_update&, std::uint64_t, const nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::packet_header&)
        { ++strategy_best_bid_and_ask_update; ++matched_messages; }
    void on_message(const nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::strategy_best_bid_update&, std::uint64_t, const nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::packet_header&)
        { ++strategy_best_bid_update; ++matched_messages; }
    void on_message(const nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::strategy_best_ask_update&, std::uint64_t, const nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::packet_header&)
        { ++strategy_best_ask_update; ++matched_messages; }
    void on_message(const nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::complex_strategy_ticker_message&, std::uint64_t, const nasdaq::iseoptions::topcomboquotefeed::itch::v1_0::packet_header&)
        { ++complex_strategy_ticker_message; ++matched_messages; }

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
        std::cout << "  SystemEventMessage (S)               " << system_event_message << std::endl;
        std::cout << "  ComplexStrategyDirectoryMessage (R)  " << complex_strategy_directory_message << std::endl;
        std::cout << "  StrategyOpenClosedMessage (O)        " << strategy_open_closed_message << std::endl;
        std::cout << "  StrategyTradingActionMessage (H)     " << strategy_trading_action_message << std::endl;
        std::cout << "  StrategyBestBidAndAskUpdate (C)      " << strategy_best_bid_and_ask_update << std::endl;
        std::cout << "  StrategyBestBidUpdate (D)            " << strategy_best_bid_update << std::endl;
        std::cout << "  StrategyBestAskUpdate (E)            " << strategy_best_ask_update << std::endl;
        std::cout << "  ComplexStrategyTickerMessage (t)     " << complex_strategy_ticker_message << std::endl;
    }
};
}
