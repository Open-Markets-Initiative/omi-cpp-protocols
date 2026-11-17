// Siac.Cqs.Output.Cta.v2.10.a: statistics/Statistics.hpp
#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/advanced/siac/cqs/output/cta/v2.10.a/messages/session.hpp"

namespace statistics {

// Siac Cta C++ statistics
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
    uint64_t symbol_reference_data_message = 0;
    uint64_t start_of_day_message = 0;
    uint64_t finra_close_message = 0;
    uint64_t reset_block_sequence_number_message = 0;
    uint64_t finra_open_message = 0;
    uint64_t disaster_recovery_data_center_activation_message = 0;
    uint64_t line_integrity_message = 0;
    uint64_t end_of_day_message = 0;
    uint64_t market_wide_circuit_breaker_decline_level_status_message = 0;
    uint64_t market_wide_circuit_breaker_status_message = 0;
    uint64_t auction_status_message = 0;
    uint64_t long_quote_message = 0;
    uint64_t short_quote_message = 0;
    uint64_t special_long_quote_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        siac::cqs::output::cta::v2_10_a::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    siac::cqs::output::cta::v2_10_a::seq_action on_transport_header(const siac::cqs::output::cta::v2_10_a::block_header& transport, const packet::Frame&) {
        total_messages += transport.messages_in_block.get().value();

        return siac::cqs::output::cta::v2_10_a::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const siac::cqs::output::cta::v2_10_a::symbol_reference_data_message&, std::uint64_t, const siac::cqs::output::cta::v2_10_a::block_header&)
        { ++symbol_reference_data_message; ++matched_messages; }
    void on_message(const siac::cqs::output::cta::v2_10_a::start_of_day_message&, std::uint64_t, const siac::cqs::output::cta::v2_10_a::block_header&)
        { ++start_of_day_message; ++matched_messages; }
    void on_message(const siac::cqs::output::cta::v2_10_a::finra_close_message&, std::uint64_t, const siac::cqs::output::cta::v2_10_a::block_header&)
        { ++finra_close_message; ++matched_messages; }
    void on_message(const siac::cqs::output::cta::v2_10_a::reset_block_sequence_number_message&, std::uint64_t, const siac::cqs::output::cta::v2_10_a::block_header&)
        { ++reset_block_sequence_number_message; ++matched_messages; }
    void on_message(const siac::cqs::output::cta::v2_10_a::finra_open_message&, std::uint64_t, const siac::cqs::output::cta::v2_10_a::block_header&)
        { ++finra_open_message; ++matched_messages; }
    void on_message(const siac::cqs::output::cta::v2_10_a::disaster_recovery_data_center_activation_message&, std::uint64_t, const siac::cqs::output::cta::v2_10_a::block_header&)
        { ++disaster_recovery_data_center_activation_message; ++matched_messages; }
    void on_message(const siac::cqs::output::cta::v2_10_a::line_integrity_message&, std::uint64_t, const siac::cqs::output::cta::v2_10_a::block_header&)
        { ++line_integrity_message; ++matched_messages; }
    void on_message(const siac::cqs::output::cta::v2_10_a::end_of_day_message&, std::uint64_t, const siac::cqs::output::cta::v2_10_a::block_header&)
        { ++end_of_day_message; ++matched_messages; }
    void on_message(const siac::cqs::output::cta::v2_10_a::market_wide_circuit_breaker_decline_level_status_message&, std::uint64_t, const siac::cqs::output::cta::v2_10_a::block_header&)
        { ++market_wide_circuit_breaker_decline_level_status_message; ++matched_messages; }
    void on_message(const siac::cqs::output::cta::v2_10_a::market_wide_circuit_breaker_status_message&, std::uint64_t, const siac::cqs::output::cta::v2_10_a::block_header&)
        { ++market_wide_circuit_breaker_status_message; ++matched_messages; }
    void on_message(const siac::cqs::output::cta::v2_10_a::auction_status_message&, std::uint64_t, const siac::cqs::output::cta::v2_10_a::block_header&)
        { ++auction_status_message; ++matched_messages; }
    void on_message(const siac::cqs::output::cta::v2_10_a::long_quote_message&, std::uint64_t, const siac::cqs::output::cta::v2_10_a::block_header&)
        { ++long_quote_message; ++matched_messages; }
    void on_message(const siac::cqs::output::cta::v2_10_a::short_quote_message&, std::uint64_t, const siac::cqs::output::cta::v2_10_a::block_header&)
        { ++short_quote_message; ++matched_messages; }
    void on_message(const siac::cqs::output::cta::v2_10_a::special_long_quote_message&, std::uint64_t, const siac::cqs::output::cta::v2_10_a::block_header&)
        { ++special_long_quote_message; ++matched_messages; }

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
        std::cout << "  SymbolReferenceDataMessage                         " << symbol_reference_data_message << std::endl;
        std::cout << "  StartOfDayMessage                                  " << start_of_day_message << std::endl;
        std::cout << "  FinraCloseMessage                                  " << finra_close_message << std::endl;
        std::cout << "  ResetBlockSequenceNumberMessage                    " << reset_block_sequence_number_message << std::endl;
        std::cout << "  FinraOpenMessage                                   " << finra_open_message << std::endl;
        std::cout << "  DisasterRecoveryDataCenterActivationMessage        " << disaster_recovery_data_center_activation_message << std::endl;
        std::cout << "  LineIntegrityMessage                               " << line_integrity_message << std::endl;
        std::cout << "  EndOfDayMessage                                    " << end_of_day_message << std::endl;
        std::cout << "  MarketWideCircuitBreakerDeclineLevelStatusMessage  " << market_wide_circuit_breaker_decline_level_status_message << std::endl;
        std::cout << "  MarketWideCircuitBreakerStatusMessage              " << market_wide_circuit_breaker_status_message << std::endl;
        std::cout << "  AuctionStatusMessage                               " << auction_status_message << std::endl;
        std::cout << "  LongQuoteMessage                                   " << long_quote_message << std::endl;
        std::cout << "  ShortQuoteMessage                                  " << short_quote_message << std::endl;
        std::cout << "  SpecialLongQuoteMessage                            " << special_long_quote_message << std::endl;
    }
};
}
