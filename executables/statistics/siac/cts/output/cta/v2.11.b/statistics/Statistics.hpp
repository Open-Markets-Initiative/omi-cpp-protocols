// Siac.Cts.Output.Cta.v2.11.b: statistics/Statistics.hpp
#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/advanced/siac/cts/output/cta/v2.11.b/messages/session.hpp"

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
    uint64_t start_of_end_of_day_summary_message = 0;
    uint64_t end_of_end_of_day_summary_message = 0;
    uint64_t start_of_start_of_day_summary_message = 0;
    uint64_t end_of_start_of_day_summary_message = 0;
    uint64_t symbol_reference_data_message = 0;
    uint64_t start_of_day_message = 0;
    uint64_t reset_block_sequence_number_message = 0;
    uint64_t disaster_recovery_data_center_activation_message = 0;
    uint64_t line_integrity_message = 0;
    uint64_t end_of_day_message = 0;
    uint64_t index_message = 0;
    uint64_t bid_and_offer_index_message = 0;
    uint64_t market_wide_circuit_breaker_decline_level_status_message = 0;
    uint64_t market_wide_circuit_breaker_status_message = 0;
    uint64_t approximate_adjusted_volume_market_center_message = 0;
    uint64_t fractional_approximate_adjusted_volume_market_center_message = 0;
    uint64_t approximate_trades_and_total_dollar_value_message = 0;
    uint64_t crossing_session_summary_message = 0;
    uint64_t prior_day_trade_correction_message = 0;
    uint64_t prior_day_trade_message = 0;
    uint64_t prior_day_trade_cancel_error_message = 0;
    uint64_t fractional_prior_day_trade_correction_message = 0;
    uint64_t fractional_prior_day_trade_message = 0;
    uint64_t fractional_prior_day_trade_cancel_error_message = 0;
    uint64_t consolidated_start_of_day_summary_message = 0;
    uint64_t participant_start_of_day_summary_message = 0;
    uint64_t consolidated_end_of_day_summary_message = 0;
    uint64_t fractional_consolidated_end_of_day_summary_message = 0;
    uint64_t participant_end_of_day_summary_message = 0;
    uint64_t fractional_participant_end_of_day_summary_message = 0;
    uint64_t auction_status_message = 0;
    uint64_t trade_correction_message = 0;
    uint64_t long_trade_message = 0;
    uint64_t short_trade_message = 0;
    uint64_t trade_cancel_error_message = 0;
    uint64_t fractional_trade_correction_message = 0;
    uint64_t fractional_long_trade_message = 0;
    uint64_t trading_status_message = 0;
    uint64_t fractional_short_trade_message = 0;
    uint64_t fractional_trade_cancel_error_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        siac::cts::output::cta::v2_11_b::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    siac::cts::output::cta::v2_11_b::seq_action on_transport_header(const siac::cts::output::cta::v2_11_b::block_header& transport, const packet::Frame&) {
        total_messages += transport.messages_in_block.get().value();

        return siac::cts::output::cta::v2_11_b::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const siac::cts::output::cta::v2_11_b::start_of_end_of_day_summary_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++start_of_end_of_day_summary_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::end_of_end_of_day_summary_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++end_of_end_of_day_summary_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::start_of_start_of_day_summary_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++start_of_start_of_day_summary_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::end_of_start_of_day_summary_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++end_of_start_of_day_summary_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::symbol_reference_data_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++symbol_reference_data_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::start_of_day_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++start_of_day_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::reset_block_sequence_number_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++reset_block_sequence_number_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::disaster_recovery_data_center_activation_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++disaster_recovery_data_center_activation_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::line_integrity_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++line_integrity_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::end_of_day_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++end_of_day_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::index_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++index_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::bid_and_offer_index_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++bid_and_offer_index_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::market_wide_circuit_breaker_decline_level_status_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++market_wide_circuit_breaker_decline_level_status_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::market_wide_circuit_breaker_status_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++market_wide_circuit_breaker_status_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::approximate_adjusted_volume_market_center_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++approximate_adjusted_volume_market_center_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::fractional_approximate_adjusted_volume_market_center_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++fractional_approximate_adjusted_volume_market_center_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::approximate_trades_and_total_dollar_value_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++approximate_trades_and_total_dollar_value_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::crossing_session_summary_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++crossing_session_summary_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::prior_day_trade_correction_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++prior_day_trade_correction_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::prior_day_trade_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++prior_day_trade_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::prior_day_trade_cancel_error_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++prior_day_trade_cancel_error_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::fractional_prior_day_trade_correction_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++fractional_prior_day_trade_correction_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::fractional_prior_day_trade_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++fractional_prior_day_trade_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::fractional_prior_day_trade_cancel_error_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++fractional_prior_day_trade_cancel_error_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::consolidated_start_of_day_summary_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++consolidated_start_of_day_summary_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::participant_start_of_day_summary_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++participant_start_of_day_summary_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::consolidated_end_of_day_summary_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++consolidated_end_of_day_summary_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::fractional_consolidated_end_of_day_summary_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++fractional_consolidated_end_of_day_summary_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::participant_end_of_day_summary_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++participant_end_of_day_summary_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::fractional_participant_end_of_day_summary_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++fractional_participant_end_of_day_summary_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::auction_status_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++auction_status_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::trade_correction_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++trade_correction_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::long_trade_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++long_trade_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::short_trade_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++short_trade_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::trade_cancel_error_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++trade_cancel_error_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::fractional_trade_correction_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++fractional_trade_correction_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::fractional_long_trade_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++fractional_long_trade_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::trading_status_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++trading_status_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::fractional_short_trade_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++fractional_short_trade_message; ++matched_messages; }
    void on_message(const siac::cts::output::cta::v2_11_b::fractional_trade_cancel_error_message&, std::uint64_t, const siac::cts::output::cta::v2_11_b::block_header&)
        { ++fractional_trade_cancel_error_message; ++matched_messages; }

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
        std::cout << "  StartOfEndOfDaySummaryMessage                           " << start_of_end_of_day_summary_message << std::endl;
        std::cout << "  EndOfEndOfDaySummaryMessage                             " << end_of_end_of_day_summary_message << std::endl;
        std::cout << "  StartOfStartOfDaySummaryMessage                         " << start_of_start_of_day_summary_message << std::endl;
        std::cout << "  EndOfStartOfDaySummaryMessage                           " << end_of_start_of_day_summary_message << std::endl;
        std::cout << "  SymbolReferenceDataMessage                              " << symbol_reference_data_message << std::endl;
        std::cout << "  StartOfDayMessage                                       " << start_of_day_message << std::endl;
        std::cout << "  ResetBlockSequenceNumberMessage                         " << reset_block_sequence_number_message << std::endl;
        std::cout << "  DisasterRecoveryDataCenterActivationMessage             " << disaster_recovery_data_center_activation_message << std::endl;
        std::cout << "  LineIntegrityMessage                                    " << line_integrity_message << std::endl;
        std::cout << "  EndOfDayMessage                                         " << end_of_day_message << std::endl;
        std::cout << "  IndexMessage                                            " << index_message << std::endl;
        std::cout << "  BidAndOfferIndexMessage                                 " << bid_and_offer_index_message << std::endl;
        std::cout << "  MarketWideCircuitBreakerDeclineLevelStatusMessage       " << market_wide_circuit_breaker_decline_level_status_message << std::endl;
        std::cout << "  MarketWideCircuitBreakerStatusMessage                   " << market_wide_circuit_breaker_status_message << std::endl;
        std::cout << "  ApproximateAdjustedVolumeMarketCenterMessage            " << approximate_adjusted_volume_market_center_message << std::endl;
        std::cout << "  FractionalApproximateAdjustedVolumeMarketCenterMessage  " << fractional_approximate_adjusted_volume_market_center_message << std::endl;
        std::cout << "  ApproximateTradesAndTotalDollarValueMessage             " << approximate_trades_and_total_dollar_value_message << std::endl;
        std::cout << "  CrossingSessionSummaryMessage                           " << crossing_session_summary_message << std::endl;
        std::cout << "  PriorDayTradeCorrectionMessage                          " << prior_day_trade_correction_message << std::endl;
        std::cout << "  PriorDayTradeMessage                                    " << prior_day_trade_message << std::endl;
        std::cout << "  PriorDayTradeCancelErrorMessage                         " << prior_day_trade_cancel_error_message << std::endl;
        std::cout << "  FractionalPriorDayTradeCorrectionMessage                " << fractional_prior_day_trade_correction_message << std::endl;
        std::cout << "  FractionalPriorDayTradeMessage                          " << fractional_prior_day_trade_message << std::endl;
        std::cout << "  FractionalPriorDayTradeCancelErrorMessage               " << fractional_prior_day_trade_cancel_error_message << std::endl;
        std::cout << "  ConsolidatedStartOfDaySummaryMessage                    " << consolidated_start_of_day_summary_message << std::endl;
        std::cout << "  ParticipantStartOfDaySummaryMessage                     " << participant_start_of_day_summary_message << std::endl;
        std::cout << "  ConsolidatedEndOfDaySummaryMessage                      " << consolidated_end_of_day_summary_message << std::endl;
        std::cout << "  FractionalConsolidatedEndOfDaySummaryMessage            " << fractional_consolidated_end_of_day_summary_message << std::endl;
        std::cout << "  ParticipantEndOfDaySummaryMessage                       " << participant_end_of_day_summary_message << std::endl;
        std::cout << "  FractionalParticipantEndOfDaySummaryMessage             " << fractional_participant_end_of_day_summary_message << std::endl;
        std::cout << "  AuctionStatusMessage                                    " << auction_status_message << std::endl;
        std::cout << "  TradeCorrectionMessage                                  " << trade_correction_message << std::endl;
        std::cout << "  LongTradeMessage                                        " << long_trade_message << std::endl;
        std::cout << "  ShortTradeMessage                                       " << short_trade_message << std::endl;
        std::cout << "  TradeCancelErrorMessage                                 " << trade_cancel_error_message << std::endl;
        std::cout << "  FractionalTradeCorrectionMessage                        " << fractional_trade_correction_message << std::endl;
        std::cout << "  FractionalLongTradeMessage                              " << fractional_long_trade_message << std::endl;
        std::cout << "  TradingStatusMessage                                    " << trading_status_message << std::endl;
        std::cout << "  FractionalShortTradeMessage                             " << fractional_short_trade_message << std::endl;
        std::cout << "  FractionalTradeCancelErrorMessage                       " << fractional_trade_cancel_error_message << std::endl;
    }
};
}
