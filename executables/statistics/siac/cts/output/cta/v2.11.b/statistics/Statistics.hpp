#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/modern/siac/cts/output/cta/v2.11.b/definitions.hpp"

namespace statistics {

// Siac Cta C++ statistics
struct Statistics {

    siac::cts::output::cta::v2_11_b::MessageIterator message;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t administrative_message = 0;
    uint64_t start_of_end_of_day_summary_message = 0;
    uint64_t end_of_end_of_day_summary_message = 0;
    uint64_t start_of_start_of_day_summary_message = 0;
    uint64_t end_of_start_of_day_summary_message = 0;
    uint64_t symbol_reference_data_message = 0;
    uint64_t control_message = 0;
    uint64_t start_of_day_message = 0;
    uint64_t reset_block_sequence_number_message = 0;
    uint64_t disaster_recovery_data_center_activation_message = 0;
    uint64_t line_integrity_message = 0;
    uint64_t end_of_day_message = 0;
    uint64_t indices_message = 0;
    uint64_t index_message = 0;
    uint64_t bid_and_offer_index_message = 0;
    uint64_t market_status_message = 0;
    uint64_t market_wide_circuit_breaker_decline_level_status_message = 0;
    uint64_t market_wide_circuit_breaker_status_message = 0;
    uint64_t approximate_adjusted_volume_market_center_message = 0;
    uint64_t fractional_approximate_adjusted_volume_market_center_message = 0;
    uint64_t approximate_trades_and_total_dollar_value_message = 0;
    uint64_t crossing_session_summary_message = 0;
    uint64_t prior_day_message = 0;
    uint64_t prior_day_trade_correction_message = 0;
    uint64_t prior_day_trade_message = 0;
    uint64_t prior_day_trade_cancel_error_message = 0;
    uint64_t fractional_prior_day_trade_correction_message = 0;
    uint64_t fractional_prior_day_trade_message = 0;
    uint64_t fractional_prior_day_trade_cancel_error_message = 0;
    uint64_t summary_message = 0;
    uint64_t consolidated_start_of_day_summary_message = 0;
    uint64_t participant_start_of_day_summary_message = 0;
    uint64_t consolidated_end_of_day_summary_message = 0;
    uint64_t fractional_consolidated_end_of_day_summary_message = 0;
    uint64_t participant_end_of_day_summary_message = 0;
    uint64_t fractional_participant_end_of_day_summary_message = 0;
    uint64_t trade_message = 0;
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

    // process a frame: every tree carrying its transport reads it
    void udp() {
        const auto& frame = parser.frame();

        if (frame.is_udp()) {
            walk_message(frame);
        }
    }

    // walk the Packet tree's datagrams
    void walk_message(const packet::Frame& frame) {
        message.initialize(frame.payload, frame.payload_len);

        while (message.next()) {
            process_message(message.message, message.message_category);
        }
    }

    // count a message of the Packet tree
    void process_message(const std::byte* pointer, const char message_category) {
        switch (message_category) {
            case 'A':
                ++total_messages;
                ++administrative_message;
                {
                    const auto* sub_header = siac::cts::output::cta::v2_11_b::AdministrativeMessage::parse(pointer);
                    const char administrative_message_type = sub_header->administrative_message_type.get();
                    switch (administrative_message_type) {
                        case 'A':
                            ++start_of_end_of_day_summary_message;
                            break;
                        case 'B':
                            ++end_of_end_of_day_summary_message;
                            break;
                        case 'C':
                            ++start_of_start_of_day_summary_message;
                            break;
                        case 'D':
                            ++end_of_start_of_day_summary_message;
                            break;
                        case 'S':
                            ++symbol_reference_data_message;
                            break;
                        default:
                            ++unknown_messages;
                            break;
                    }
                }
                break;
            case 'C':
                ++total_messages;
                ++control_message;
                {
                    const auto* sub_header = siac::cts::output::cta::v2_11_b::ControlMessage::parse(pointer);
                    const char control_message_type = sub_header->control_message_type.get();
                    switch (control_message_type) {
                        case 'A':
                            ++start_of_day_message;
                            break;
                        case 'L':
                            ++reset_block_sequence_number_message;
                            break;
                        case 'P':
                            ++disaster_recovery_data_center_activation_message;
                            break;
                        case 'T':
                            ++line_integrity_message;
                            break;
                        case 'Z':
                            ++end_of_day_message;
                            break;
                        default:
                            ++unknown_messages;
                            break;
                    }
                }
                break;
            case 'I':
                ++total_messages;
                ++indices_message;
                {
                    const auto* sub_header = siac::cts::output::cta::v2_11_b::IndicesMessage::parse(pointer);
                    const char indices_message_type = sub_header->indices_message_type.get();
                    switch (indices_message_type) {
                        case 'I':
                            ++index_message;
                            break;
                        case 'Q':
                            ++bid_and_offer_index_message;
                            break;
                        default:
                            ++unknown_messages;
                            break;
                    }
                }
                break;
            case 'M':
                ++total_messages;
                ++market_status_message;
                {
                    const auto* sub_header = siac::cts::output::cta::v2_11_b::MarketStatusMessage::parse(pointer);
                    const char market_status_message_type = sub_header->market_status_message_type.get();
                    switch (market_status_message_type) {
                        case 'K':
                            ++market_wide_circuit_breaker_decline_level_status_message;
                            break;
                        case 'L':
                            ++market_wide_circuit_breaker_status_message;
                            break;
                        case 'N':
                            ++approximate_adjusted_volume_market_center_message;
                            break;
                        case 'V':
                            ++fractional_approximate_adjusted_volume_market_center_message;
                            break;
                        case 'O':
                            ++approximate_trades_and_total_dollar_value_message;
                            break;
                        case 'P':
                            ++crossing_session_summary_message;
                            break;
                        default:
                            ++unknown_messages;
                            break;
                    }
                }
                break;
            case 'P':
                ++total_messages;
                ++prior_day_message;
                {
                    const auto* sub_header = siac::cts::output::cta::v2_11_b::PriorDayMessage::parse(pointer);
                    const char prior_day_message_type = sub_header->prior_day_message_type.get();
                    switch (prior_day_message_type) {
                        case 'C':
                            ++prior_day_trade_correction_message;
                            break;
                        case 'T':
                            ++prior_day_trade_message;
                            break;
                        case 'X':
                            ++prior_day_trade_cancel_error_message;
                            break;
                        case 'O':
                            ++fractional_prior_day_trade_correction_message;
                            break;
                        case 'R':
                            ++fractional_prior_day_trade_message;
                            break;
                        case 'E':
                            ++fractional_prior_day_trade_cancel_error_message;
                            break;
                        default:
                            ++unknown_messages;
                            break;
                    }
                }
                break;
            case 'S':
                ++total_messages;
                ++summary_message;
                {
                    const auto* sub_header = siac::cts::output::cta::v2_11_b::SummaryMessage::parse(pointer);
                    const char summary_message_type = sub_header->summary_message_type.get();
                    switch (summary_message_type) {
                        case 'A':
                            ++consolidated_start_of_day_summary_message;
                            break;
                        case 'B':
                            ++participant_start_of_day_summary_message;
                            break;
                        case 'C':
                            ++consolidated_end_of_day_summary_message;
                            break;
                        case 'T':
                            ++fractional_consolidated_end_of_day_summary_message;
                            break;
                        case 'D':
                            ++participant_end_of_day_summary_message;
                            break;
                        case 'P':
                            ++fractional_participant_end_of_day_summary_message;
                            break;
                        default:
                            ++unknown_messages;
                            break;
                    }
                }
                break;
            case 'T':
                ++total_messages;
                ++trade_message;
                {
                    const auto* sub_header = siac::cts::output::cta::v2_11_b::TradeMessage::parse(pointer);
                    const char trade_message_type = sub_header->trade_message_type.get();
                    switch (trade_message_type) {
                        case 'A':
                            ++auction_status_message;
                            break;
                        case 'C':
                            ++trade_correction_message;
                            break;
                        case 'L':
                            ++long_trade_message;
                            break;
                        case 'T':
                            ++short_trade_message;
                            break;
                        case 'X':
                            ++trade_cancel_error_message;
                            break;
                        case 'O':
                            ++fractional_trade_correction_message;
                            break;
                        case 'R':
                            ++fractional_long_trade_message;
                            break;
                        case 'S':
                            ++trading_status_message;
                            break;
                        case 'H':
                            ++fractional_short_trade_message;
                            break;
                        case 'E':
                            ++fractional_trade_cancel_error_message;
                            break;
                        default:
                            ++unknown_messages;
                            break;
                    }
                }
                break;

            default:
                ++total_messages;
                ++unknown_messages;
                if (options.verbose) {
                    std::cerr << "Unknown message_category: " << static_cast<int>(message_category) << std::endl;
                }
                break;
        }
    }

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
        std::cout << "  AdministrativeMessage (A)                                   " << administrative_message << std::endl;
        std::cout << "  StartOfEndOfDaySummaryMessage (A)                           " << start_of_end_of_day_summary_message << std::endl;
        std::cout << "  EndOfEndOfDaySummaryMessage (B)                             " << end_of_end_of_day_summary_message << std::endl;
        std::cout << "  StartOfStartOfDaySummaryMessage (C)                         " << start_of_start_of_day_summary_message << std::endl;
        std::cout << "  EndOfStartOfDaySummaryMessage (D)                           " << end_of_start_of_day_summary_message << std::endl;
        std::cout << "  SymbolReferenceDataMessage (S)                              " << symbol_reference_data_message << std::endl;
        std::cout << "  ControlMessage (C)                                          " << control_message << std::endl;
        std::cout << "  StartOfDayMessage (A)                                       " << start_of_day_message << std::endl;
        std::cout << "  ResetBlockSequenceNumberMessage (L)                         " << reset_block_sequence_number_message << std::endl;
        std::cout << "  DisasterRecoveryDataCenterActivationMessage (P)             " << disaster_recovery_data_center_activation_message << std::endl;
        std::cout << "  LineIntegrityMessage (T)                                    " << line_integrity_message << std::endl;
        std::cout << "  EndOfDayMessage (Z)                                         " << end_of_day_message << std::endl;
        std::cout << "  IndicesMessage (I)                                          " << indices_message << std::endl;
        std::cout << "  IndexMessage (I)                                            " << index_message << std::endl;
        std::cout << "  BidAndOfferIndexMessage (Q)                                 " << bid_and_offer_index_message << std::endl;
        std::cout << "  MarketStatusMessage (M)                                     " << market_status_message << std::endl;
        std::cout << "  MarketWideCircuitBreakerDeclineLevelStatusMessage (K)       " << market_wide_circuit_breaker_decline_level_status_message << std::endl;
        std::cout << "  MarketWideCircuitBreakerStatusMessage (L)                   " << market_wide_circuit_breaker_status_message << std::endl;
        std::cout << "  ApproximateAdjustedVolumeMarketCenterMessage (N)            " << approximate_adjusted_volume_market_center_message << std::endl;
        std::cout << "  FractionalApproximateAdjustedVolumeMarketCenterMessage (V)  " << fractional_approximate_adjusted_volume_market_center_message << std::endl;
        std::cout << "  ApproximateTradesAndTotalDollarValueMessage (O)             " << approximate_trades_and_total_dollar_value_message << std::endl;
        std::cout << "  CrossingSessionSummaryMessage (P)                           " << crossing_session_summary_message << std::endl;
        std::cout << "  PriorDayMessage (P)                                         " << prior_day_message << std::endl;
        std::cout << "  PriorDayTradeCorrectionMessage (C)                          " << prior_day_trade_correction_message << std::endl;
        std::cout << "  PriorDayTradeMessage (T)                                    " << prior_day_trade_message << std::endl;
        std::cout << "  PriorDayTradeCancelErrorMessage (X)                         " << prior_day_trade_cancel_error_message << std::endl;
        std::cout << "  FractionalPriorDayTradeCorrectionMessage (O)                " << fractional_prior_day_trade_correction_message << std::endl;
        std::cout << "  FractionalPriorDayTradeMessage (R)                          " << fractional_prior_day_trade_message << std::endl;
        std::cout << "  FractionalPriorDayTradeCancelErrorMessage (E)               " << fractional_prior_day_trade_cancel_error_message << std::endl;
        std::cout << "  SummaryMessage (S)                                          " << summary_message << std::endl;
        std::cout << "  ConsolidatedStartOfDaySummaryMessage (A)                    " << consolidated_start_of_day_summary_message << std::endl;
        std::cout << "  ParticipantStartOfDaySummaryMessage (B)                     " << participant_start_of_day_summary_message << std::endl;
        std::cout << "  ConsolidatedEndOfDaySummaryMessage (C)                      " << consolidated_end_of_day_summary_message << std::endl;
        std::cout << "  FractionalConsolidatedEndOfDaySummaryMessage (T)            " << fractional_consolidated_end_of_day_summary_message << std::endl;
        std::cout << "  ParticipantEndOfDaySummaryMessage (D)                       " << participant_end_of_day_summary_message << std::endl;
        std::cout << "  FractionalParticipantEndOfDaySummaryMessage (P)             " << fractional_participant_end_of_day_summary_message << std::endl;
        std::cout << "  TradeMessage (T)                                            " << trade_message << std::endl;
        std::cout << "  AuctionStatusMessage (A)                                    " << auction_status_message << std::endl;
        std::cout << "  TradeCorrectionMessage (C)                                  " << trade_correction_message << std::endl;
        std::cout << "  LongTradeMessage (L)                                        " << long_trade_message << std::endl;
        std::cout << "  ShortTradeMessage (T)                                       " << short_trade_message << std::endl;
        std::cout << "  TradeCancelErrorMessage (X)                                 " << trade_cancel_error_message << std::endl;
        std::cout << "  FractionalTradeCorrectionMessage (O)                        " << fractional_trade_correction_message << std::endl;
        std::cout << "  FractionalLongTradeMessage (R)                              " << fractional_long_trade_message << std::endl;
        std::cout << "  TradingStatusMessage (S)                                    " << trading_status_message << std::endl;
        std::cout << "  FractionalShortTradeMessage (H)                             " << fractional_short_trade_message << std::endl;
        std::cout << "  FractionalTradeCancelErrorMessage (E)                       " << fractional_trade_cancel_error_message << std::endl;
    }
};
}
