// OtcMarkets.LinkAts.Multicast.Link.v4.3: statistics/Statistics.hpp
#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/advanced/otcmarkets/linkats/multicast/link/v4.3/messages/session.hpp"

namespace statistics {

// OtcMarkets Link C++ statistics
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
    uint64_t start_of_spin_message = 0;
    uint64_t end_of_spin_message = 0;
    uint64_t market_open_message = 0;
    uint64_t market_close_message = 0;
    uint64_t security_message = 0;
    uint64_t quote_message = 0;
    uint64_t quote_update_message = 0;
    uint64_t inside_message = 0;
    uint64_t inside_update_message = 0;
    uint64_t reference_price_message = 0;
    uint64_t reference_price_update_message = 0;
    uint64_t extended_security_message = 0;
    uint64_t extended_security_no_cusip_message = 0;
    uint64_t trade_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        otcmarkets::linkats::multicast::link::v4_3::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    otcmarkets::linkats::multicast::link::v4_3::seq_action on_transport_header(const otcmarkets::linkats::multicast::link::v4_3::packet_header& transport, const packet::Frame&) {
        total_messages += transport.message_count.get().value();

        return otcmarkets::linkats::multicast::link::v4_3::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const otcmarkets::linkats::multicast::link::v4_3::start_of_spin_message&, std::uint64_t, const otcmarkets::linkats::multicast::link::v4_3::packet_header&)
        { ++start_of_spin_message; ++matched_messages; }
    void on_message(const otcmarkets::linkats::multicast::link::v4_3::end_of_spin_message&, std::uint64_t, const otcmarkets::linkats::multicast::link::v4_3::packet_header&)
        { ++end_of_spin_message; ++matched_messages; }
    void on_message(const otcmarkets::linkats::multicast::link::v4_3::market_open_message&, std::uint64_t, const otcmarkets::linkats::multicast::link::v4_3::packet_header&)
        { ++market_open_message; ++matched_messages; }
    void on_message(const otcmarkets::linkats::multicast::link::v4_3::market_close_message&, std::uint64_t, const otcmarkets::linkats::multicast::link::v4_3::packet_header&)
        { ++market_close_message; ++matched_messages; }
    void on_message(const otcmarkets::linkats::multicast::link::v4_3::security_message&, std::uint64_t, const otcmarkets::linkats::multicast::link::v4_3::packet_header&)
        { ++security_message; ++matched_messages; }
    void on_message(const otcmarkets::linkats::multicast::link::v4_3::quote_message&, std::uint64_t, const otcmarkets::linkats::multicast::link::v4_3::packet_header&)
        { ++quote_message; ++matched_messages; }
    void on_message(const otcmarkets::linkats::multicast::link::v4_3::quote_update_message&, std::uint64_t, const otcmarkets::linkats::multicast::link::v4_3::packet_header&)
        { ++quote_update_message; ++matched_messages; }
    void on_message(const otcmarkets::linkats::multicast::link::v4_3::inside_message&, std::uint64_t, const otcmarkets::linkats::multicast::link::v4_3::packet_header&)
        { ++inside_message; ++matched_messages; }
    void on_message(const otcmarkets::linkats::multicast::link::v4_3::inside_update_message&, std::uint64_t, const otcmarkets::linkats::multicast::link::v4_3::packet_header&)
        { ++inside_update_message; ++matched_messages; }
    void on_message(const otcmarkets::linkats::multicast::link::v4_3::reference_price_message&, std::uint64_t, const otcmarkets::linkats::multicast::link::v4_3::packet_header&)
        { ++reference_price_message; ++matched_messages; }
    void on_message(const otcmarkets::linkats::multicast::link::v4_3::reference_price_update_message&, std::uint64_t, const otcmarkets::linkats::multicast::link::v4_3::packet_header&)
        { ++reference_price_update_message; ++matched_messages; }
    void on_message(const otcmarkets::linkats::multicast::link::v4_3::extended_security_message&, std::uint64_t, const otcmarkets::linkats::multicast::link::v4_3::packet_header&)
        { ++extended_security_message; ++matched_messages; }
    void on_message(const otcmarkets::linkats::multicast::link::v4_3::extended_security_no_cusip_message&, std::uint64_t, const otcmarkets::linkats::multicast::link::v4_3::packet_header&)
        { ++extended_security_no_cusip_message; ++matched_messages; }
    void on_message(const otcmarkets::linkats::multicast::link::v4_3::trade_message&, std::uint64_t, const otcmarkets::linkats::multicast::link::v4_3::packet_header&)
        { ++trade_message; ++matched_messages; }

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
        std::cout << "  StartOfSpinMessage (11)              " << start_of_spin_message << std::endl;
        std::cout << "  EndOfSpinMessage (12)                " << end_of_spin_message << std::endl;
        std::cout << "  MarketOpenMessage (13)               " << market_open_message << std::endl;
        std::cout << "  MarketCloseMessage (14)              " << market_close_message << std::endl;
        std::cout << "  SecurityMessage (9)                  " << security_message << std::endl;
        std::cout << "  QuoteMessage (1)                     " << quote_message << std::endl;
        std::cout << "  QuoteUpdateMessage (2)               " << quote_update_message << std::endl;
        std::cout << "  InsideMessage (3)                    " << inside_message << std::endl;
        std::cout << "  InsideUpdateMessage (4)              " << inside_update_message << std::endl;
        std::cout << "  ReferencePriceMessage (7)            " << reference_price_message << std::endl;
        std::cout << "  ReferencePriceUpdateMessage (8)      " << reference_price_update_message << std::endl;
        std::cout << "  ExtendedSecurityMessage (15)         " << extended_security_message << std::endl;
        std::cout << "  ExtendedSecurityNoCusipMessage (16)  " << extended_security_no_cusip_message << std::endl;
        std::cout << "  TradeMessage (17)                    " << trade_message << std::endl;
    }
};
}
