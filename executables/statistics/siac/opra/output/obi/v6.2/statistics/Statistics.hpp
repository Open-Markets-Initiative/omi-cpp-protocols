#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/advanced/siac/opra/output/obi/v6.2/messages/session.hpp"

namespace statistics {

// Siac Obi C++ statistics
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
    uint64_t administrative_message = 0;
    uint64_t control_message = 0;
    uint64_t equity_and_index_last_sale_message = 0;
    uint64_t open_interest_message = 0;
    uint64_t equity_and_index_end_of_day_summary_message = 0;
    uint64_t long_equity_and_index_quote_message = 0;
    uint64_t short_equity_and_index_quote_message = 0;
    uint64_t underlying_value_last_sale_message = 0;
    uint64_t underlying_value_bid_and_offer_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        siac::opra::output::obi::v6_2::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    siac::opra::output::obi::v6_2::seq_action on_transport_header(const siac::opra::output::obi::v6_2::block_header& transport, const packet::Frame&) {
        total_messages += transport.messages_in_block.get().value();

        return siac::opra::output::obi::v6_2::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const siac::opra::output::obi::v6_2::administrative_message&, std::uint64_t, const siac::opra::output::obi::v6_2::block_header&)
        { ++administrative_message; ++matched_messages; }
    void on_message(const siac::opra::output::obi::v6_2::control_message&, std::uint64_t, const siac::opra::output::obi::v6_2::block_header&)
        { ++control_message; ++matched_messages; }
    void on_message(const siac::opra::output::obi::v6_2::equity_and_index_last_sale_message&, std::uint64_t, const siac::opra::output::obi::v6_2::block_header&)
        { ++equity_and_index_last_sale_message; ++matched_messages; }
    void on_message(const siac::opra::output::obi::v6_2::open_interest_message&, std::uint64_t, const siac::opra::output::obi::v6_2::block_header&)
        { ++open_interest_message; ++matched_messages; }
    void on_message(const siac::opra::output::obi::v6_2::equity_and_index_end_of_day_summary_message&, std::uint64_t, const siac::opra::output::obi::v6_2::block_header&)
        { ++equity_and_index_end_of_day_summary_message; ++matched_messages; }
    void on_message(const siac::opra::output::obi::v6_2::long_equity_and_index_quote_message&, std::uint64_t, const siac::opra::output::obi::v6_2::block_header&)
        { ++long_equity_and_index_quote_message; ++matched_messages; }
    void on_message(const siac::opra::output::obi::v6_2::short_equity_and_index_quote_message&, std::uint64_t, const siac::opra::output::obi::v6_2::block_header&)
        { ++short_equity_and_index_quote_message; ++matched_messages; }
    void on_message(const siac::opra::output::obi::v6_2::underlying_value_last_sale_message&, std::uint64_t, const siac::opra::output::obi::v6_2::block_header&)
        { ++underlying_value_last_sale_message; ++matched_messages; }
    void on_message(const siac::opra::output::obi::v6_2::underlying_value_bid_and_offer_message&, std::uint64_t, const siac::opra::output::obi::v6_2::block_header&)
        { ++underlying_value_bid_and_offer_message; ++matched_messages; }

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
        std::cout << "  AdministrativeMessage                 " << administrative_message << std::endl;
        std::cout << "  ControlMessage                        " << control_message << std::endl;
        std::cout << "  EquityAndIndexLastSaleMessage         " << equity_and_index_last_sale_message << std::endl;
        std::cout << "  OpenInterestMessage                   " << open_interest_message << std::endl;
        std::cout << "  EquityAndIndexEndOfDaySummaryMessage  " << equity_and_index_end_of_day_summary_message << std::endl;
        std::cout << "  LongEquityAndIndexQuoteMessage        " << long_equity_and_index_quote_message << std::endl;
        std::cout << "  ShortEquityAndIndexQuoteMessage       " << short_equity_and_index_quote_message << std::endl;
        std::cout << "  UnderlyingValueLastSaleMessage        " << underlying_value_last_sale_message << std::endl;
        std::cout << "  UnderlyingValueBidAndOfferMessage     " << underlying_value_bid_and_offer_message << std::endl;
    }
};
}
