// Siac.Cts.Output.Cta.v2.9 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/siac/cts/output/cta/v2.9.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/modern/siac/cts/output/cta/v2.9/definitions.hpp"

namespace protocol = ::siac::cts::output::cta::v2_9;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.block_header->version.get());
    checksum += bench::digest(iterator.block_header->block_size.get());
    checksum += bench::digest(iterator.block_header->data_feed_indicator.get());
    checksum += bench::digest(iterator.block_header->retransmission_indicator.get());
    checksum += bench::digest(iterator.block_header->block_sequence_number.get());
    checksum += bench::digest(iterator.block_header->messages_in_block.get());
    checksum += bench::digest(iterator.block_header->sip_block_timestamp.seconds.get());
    checksum += bench::digest(iterator.block_header->sip_block_timestamp.nanoseconds.get());
    checksum += bench::digest(iterator.block_header->block_checksum.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->message_length.get());
        checksum += bench::digest(iterator.message_header->message_category.get());

        if (iterator.message_category == 'A') {
            [[maybe_unused]] const auto* message = protocol::AdministrativeMessage::parse(iterator.message);
            checksum += bench::digest(message->administrative_message_type.get());
            if (message->administrative_message_type.get() == 'A') {
                [[maybe_unused]] const auto* message_2 = protocol::StartOfEndOfDayMessage::parse(iterator.message + sizeof(protocol::AdministrativeMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
            } else if (message->administrative_message_type.get() == 'B') {
                [[maybe_unused]] const auto* message_2 = protocol::EndOfEndOfDayMessage::parse(iterator.message + sizeof(protocol::AdministrativeMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
            } else if (message->administrative_message_type.get() == 'C') {
                [[maybe_unused]] const auto* message_2 = protocol::StartOfStartOfDayMessage::parse(iterator.message + sizeof(protocol::AdministrativeMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
            } else if (message->administrative_message_type.get() == 'D') {
                [[maybe_unused]] const auto* message_2 = protocol::EndOfStartOfDayMessage::parse(iterator.message + sizeof(protocol::AdministrativeMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
            }
        } else if (iterator.message_category == 'C') {
            [[maybe_unused]] const auto* message = protocol::ControlMessage::parse(iterator.message);
            checksum += bench::digest(message->control_message_type.get());
            if (message->control_message_type.get() == 'A') {
                [[maybe_unused]] const auto* message_2 = protocol::StartOfDayMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'L') {
                [[maybe_unused]] const auto* message_2 = protocol::ResetBlockSequenceNumberMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'P') {
                [[maybe_unused]] const auto* message_2 = protocol::DisasterRecoveryDataCenterActivationMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'T') {
                [[maybe_unused]] const auto* message_2 = protocol::LineIntegrityMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'Z') {
                [[maybe_unused]] const auto* message_2 = protocol::EndOfDayMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
            }
        } else if (iterator.message_category == 'I') {
            [[maybe_unused]] const auto* message = protocol::IndicesMessage::parse(iterator.message);
            checksum += bench::digest(message->indices_message_type.get());
            if (message->indices_message_type.get() == 'I') {
                [[maybe_unused]] const auto* message_2 = protocol::IndexMessage::parse(iterator.message + sizeof(protocol::IndicesMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->index_symbol.get());
                checksum += bench::digest(message_2->index_value.integer());
            } else if (message->indices_message_type.get() == 'Q') {
                [[maybe_unused]] const auto* message_2 = protocol::BidAndOfferIndexMessage::parse(iterator.message + sizeof(protocol::IndicesMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->index_symbol.get());
                checksum += bench::digest(message_2->bid_index_value.integer());
                checksum += bench::digest(message_2->offer_index_value.integer());
            }
        } else if (iterator.message_category == 'M') {
            [[maybe_unused]] const auto* message = protocol::MarketStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->market_status_message_type.get());
            if (message->market_status_message_type.get() == 'K') {
                [[maybe_unused]] const auto* message_2 = protocol::MarketWideCircuitBreakerDeclineLevelStatusMessage::parse(iterator.message + sizeof(protocol::MarketStatusMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->mwcb_level_1.integer());
                checksum += bench::digest(message_2->mwcb_level_2.integer());
                checksum += bench::digest(message_2->mwcb_level_3.integer());
                checksum += bench::digest(message_2->reserved.get());
            } else if (message->market_status_message_type.get() == 'L') {
                [[maybe_unused]] const auto* message_2 = protocol::MarketWideCircuitBreakerStatusMessage::parse(iterator.message + sizeof(protocol::MarketStatusMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->market_wide_circuit_breaker_level_indicator.get());
                checksum += bench::digest(message_2->reserved.get());
            } else if (message->market_status_message_type.get() == 'N') {
                [[maybe_unused]] const auto* message_2 = protocol::ApproximateAdjustedVolumeMarketCenterMessage::parse(iterator.message + sizeof(protocol::MarketStatusMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->number_of_participants.get());
            } else if (message->market_status_message_type.get() == 'O') {
                [[maybe_unused]] const auto* message_2 = protocol::ApproximateTradesAndTotalDollarValueMessage::parse(iterator.message + sizeof(protocol::MarketStatusMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->total_trades.get());
                checksum += bench::digest(message_2->dollar_value.integer());
            } else if (message->market_status_message_type.get() == 'P') {
                [[maybe_unused]] const auto* message_2 = protocol::CrossingSessionSummaryMessage::parse(iterator.message + sizeof(protocol::MarketStatusMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->crossing_session_i_total_trades_volume.get());
                checksum += bench::digest(message_2->crossing_session_ii_dollar_value.integer());
                checksum += bench::digest(message_2->crossing_session_ii_total_trades_volume.get());
            }
        } else if (iterator.message_category == 'P') {
            [[maybe_unused]] const auto* message = protocol::PriorDayMessage::parse(iterator.message);
            checksum += bench::digest(message->prior_day_message_type.get());
            if (message->prior_day_message_type.get() == 'C') {
                [[maybe_unused]] const auto* message_2 = protocol::PriorDayTradeCorrectionMessage::parse(iterator.message + sizeof(protocol::PriorDayMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol.get());
                checksum += bench::digest(message_2->instrument_type.get());
                checksum += bench::digest(message_2->corrected_trade.sale_conditions.settlement_type.get());
                checksum += bench::digest(message_2->corrected_trade.sale_conditions.trade_through_exempt_reason.get());
                checksum += bench::digest(message_2->corrected_trade.sale_conditions.extended_hours_or_sequence_type.get());
                checksum += bench::digest(message_2->corrected_trade.sale_conditions.sro_trade_detail.get());
                checksum += bench::digest(message_2->corrected_trade.trade_price.integer());
                checksum += bench::digest(message_2->corrected_trade.trade_volume.get());
                checksum += bench::digest(message_2->corrected_trade.sellers_sale_days.get());
                checksum += bench::digest(message_2->corrected_trade.stop_stock_indicator.get());
                checksum += bench::digest(message_2->corrected_trade.trade_through_exempt_indicator.get());
                checksum += bench::digest(message_2->corrected_trade.short_sale_restriction_indicator.get());
                checksum += bench::digest(message_2->corrected_trade.prior_day_trade_date_and_time.seconds.get());
                checksum += bench::digest(message_2->corrected_trade.prior_day_trade_date_and_time.nanoseconds.get());
                checksum += bench::digest(message_2->trade_reporting_facility_id.get());
                checksum += bench::digest(message_2->original_trade.sale_conditions.settlement_type.get());
                checksum += bench::digest(message_2->original_trade.sale_conditions.trade_through_exempt_reason.get());
                checksum += bench::digest(message_2->original_trade.sale_conditions.extended_hours_or_sequence_type.get());
                checksum += bench::digest(message_2->original_trade.sale_conditions.sro_trade_detail.get());
                checksum += bench::digest(message_2->original_trade.trade_price.integer());
                checksum += bench::digest(message_2->original_trade.trade_volume.get());
                checksum += bench::digest(message_2->original_trade.sellers_sale_days.get());
                checksum += bench::digest(message_2->original_trade.stop_stock_indicator.get());
                checksum += bench::digest(message_2->original_trade.trade_through_exempt_indicator.get());
                checksum += bench::digest(message_2->original_trade.short_sale_restriction_indicator.get());
                checksum += bench::digest(message_2->original_trade.prior_day_trade_date_and_time.seconds.get());
                checksum += bench::digest(message_2->original_trade.prior_day_trade_date_and_time.nanoseconds.get());
            } else if (message->prior_day_message_type.get() == 'T') {
                [[maybe_unused]] const auto* message_2 = protocol::PriorDayTradeMessage::parse(iterator.message + sizeof(protocol::PriorDayMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol.get());
                checksum += bench::digest(message_2->instrument_type.get());
                checksum += bench::digest(message_2->sale_conditions.settlement_type.get());
                checksum += bench::digest(message_2->sale_conditions.trade_through_exempt_reason.get());
                checksum += bench::digest(message_2->sale_conditions.extended_hours_or_sequence_type.get());
                checksum += bench::digest(message_2->sale_conditions.sro_trade_detail.get());
                checksum += bench::digest(message_2->trade_price.integer());
                checksum += bench::digest(message_2->trade_volume.get());
                checksum += bench::digest(message_2->sellers_sale_days.get());
                checksum += bench::digest(message_2->stop_stock_indicator.get());
                checksum += bench::digest(message_2->trade_through_exempt_indicator.get());
                checksum += bench::digest(message_2->short_sale_restriction_indicator.get());
                checksum += bench::digest(message_2->trade_reporting_facility_id.get());
                checksum += bench::digest(message_2->prior_day_trade_date_and_time.seconds.get());
                checksum += bench::digest(message_2->prior_day_trade_date_and_time.nanoseconds.get());
            } else if (message->prior_day_message_type.get() == 'X') {
                [[maybe_unused]] const auto* message_2 = protocol::PriorDayTradeCancelErrorMessage::parse(iterator.message + sizeof(protocol::PriorDayMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol.get());
                checksum += bench::digest(message_2->instrument_type.get());
                checksum += bench::digest(message_2->sale_conditions.settlement_type.get());
                checksum += bench::digest(message_2->sale_conditions.trade_through_exempt_reason.get());
                checksum += bench::digest(message_2->sale_conditions.extended_hours_or_sequence_type.get());
                checksum += bench::digest(message_2->sale_conditions.sro_trade_detail.get());
                checksum += bench::digest(message_2->trade_price.integer());
                checksum += bench::digest(message_2->trade_volume.get());
                checksum += bench::digest(message_2->sellers_sale_days.get());
                checksum += bench::digest(message_2->stop_stock_indicator.get());
                checksum += bench::digest(message_2->trade_through_exempt_indicator.get());
                checksum += bench::digest(message_2->short_sale_restriction_indicator.get());
                checksum += bench::digest(message_2->trade_reporting_facility_id.get());
                checksum += bench::digest(message_2->prior_day_trade_date_and_time.seconds.get());
                checksum += bench::digest(message_2->prior_day_trade_date_and_time.nanoseconds.get());
                checksum += bench::digest(message_2->cancel_error_action.get());
            }
        } else if (iterator.message_category == 'S') {
            [[maybe_unused]] const auto* message = protocol::SummaryMessage::parse(iterator.message);
            checksum += bench::digest(message->summary_message_type.get());
            if (message->summary_message_type.get() == 'A') {
                [[maybe_unused]] const auto* message_2 = protocol::ConsolidatedStartOfDaySummaryMessage::parse(iterator.message + sizeof(protocol::SummaryMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol.get());
                checksum += bench::digest(message_2->instrument_type.get());
                checksum += bench::digest(message_2->summary_participant_id.get());
                checksum += bench::digest(message_2->previous_close_price_date.get());
                checksum += bench::digest(message_2->previous_close_price.integer());
                checksum += bench::digest(message_2->short_sale_restriction_indicator.get());
                checksum += bench::digest(message_2->primary_listing_market_participant_id.get());
                checksum += bench::digest(message_2->financial_status_indicator.get());
                checksum += bench::digest(message_2->number_of_participants.get());
            } else if (message->summary_message_type.get() == 'B') {
                [[maybe_unused]] const auto* message_2 = protocol::ParticipantStartOfDaySummaryMessage::parse(iterator.message + sizeof(protocol::SummaryMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol.get());
                checksum += bench::digest(message_2->instrument_type.get());
                checksum += bench::digest(message_2->summary_participant_id.get());
                checksum += bench::digest(message_2->previous_close_price_date.get());
                checksum += bench::digest(message_2->previous_close_price.integer());
            } else if (message->summary_message_type.get() == 'C') {
                [[maybe_unused]] const auto* message_2 = protocol::ConsolidatedEndOfDaySummaryMessage::parse(iterator.message + sizeof(protocol::SummaryMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol.get());
                checksum += bench::digest(message_2->instrument_type.get());
                checksum += bench::digest(message_2->last_participant_id.get());
                checksum += bench::digest(message_2->previous_close_price_date.get());
                checksum += bench::digest(message_2->last_price.integer());
                checksum += bench::digest(message_2->high_price.integer());
                checksum += bench::digest(message_2->low_price.integer());
                checksum += bench::digest(message_2->total_volume.get());
                checksum += bench::digest(message_2->short_sale_restriction_indicator.get());
                checksum += bench::digest(message_2->primary_listing_market_participant_id.get());
                checksum += bench::digest(message_2->financial_status_indicator.get());
                checksum += bench::digest(message_2->number_of_participants.get());
            } else if (message->summary_message_type.get() == 'D') {
                [[maybe_unused]] const auto* message_2 = protocol::ParticipantEndOfDaySummaryMessage::parse(iterator.message + sizeof(protocol::SummaryMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol.get());
                checksum += bench::digest(message_2->instrument_type.get());
                checksum += bench::digest(message_2->initiating_participant_id.get());
                checksum += bench::digest(message_2->previous_close_price_date.get());
                checksum += bench::digest(message_2->last_price.integer());
                checksum += bench::digest(message_2->high_price.integer());
                checksum += bench::digest(message_2->low_price.integer());
                checksum += bench::digest(message_2->open_price.integer());
                checksum += bench::digest(message_2->total_volume.get());
                checksum += bench::digest(message_2->tick.get());
            }
        } else if (iterator.message_category == 'T') {
            [[maybe_unused]] const auto* message = protocol::TradeMessage::parse(iterator.message);
            checksum += bench::digest(message->trade_message_type.get());
            if (message->trade_message_type.get() == 'A') {
                [[maybe_unused]] const auto* message_2 = protocol::AuctionStatusMessage::parse(iterator.message + sizeof(protocol::TradeMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol.get());
                checksum += bench::digest(message_2->instrument_type.get());
                checksum += bench::digest(message_2->auction_collar_reference_price.integer());
                checksum += bench::digest(message_2->auction_collar_upper_threshold_price.integer());
                checksum += bench::digest(message_2->auction_collar_lower_threshold_price.integer());
                checksum += bench::digest(message_2->number_of_extensions.get());
                checksum += bench::digest(message_2->short_sale_restriction_indicator.get());
                checksum += bench::digest(message_2->primary_listing_market_participant_id.get());
                checksum += bench::digest(message_2->financial_status_indicator.get());
                checksum += bench::digest(message_2->future_use.get());
            } else if (message->trade_message_type.get() == 'C') {
                [[maybe_unused]] const auto* message_2 = protocol::TradeCorrectionMessage::parse(iterator.message + sizeof(protocol::TradeMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol.get());
                checksum += bench::digest(message_2->instrument_type.get());
                checksum += bench::digest(message_2->corrected_trade.sale_conditions.settlement_type.get());
                checksum += bench::digest(message_2->corrected_trade.sale_conditions.trade_through_exempt_reason.get());
                checksum += bench::digest(message_2->corrected_trade.sale_conditions.extended_hours_or_sequence_type.get());
                checksum += bench::digest(message_2->corrected_trade.sale_conditions.sro_trade_detail.get());
                checksum += bench::digest(message_2->corrected_trade.trade_price.integer());
                checksum += bench::digest(message_2->corrected_trade.trade_volume.get());
                checksum += bench::digest(message_2->corrected_trade.sellers_sale_days.get());
                checksum += bench::digest(message_2->corrected_trade.stop_stock_indicator.get());
                checksum += bench::digest(message_2->corrected_trade.trade_through_exempt_indicator.get());
                checksum += bench::digest(message_2->corrected_trade.short_sale_restriction_indicator.get());
                checksum += bench::digest(message_2->corrected_trade.prior_day_trade_date_and_time.seconds.get());
                checksum += bench::digest(message_2->corrected_trade.prior_day_trade_date_and_time.nanoseconds.get());
                checksum += bench::digest(message_2->trade_reporting_facility_id.get());
                checksum += bench::digest(message_2->timestamp_2.seconds.get());
                checksum += bench::digest(message_2->timestamp_2.nanoseconds.get());
                checksum += bench::digest(message_2->original_participant_reference_number.get());
                checksum += bench::digest(message_2->original_trade.sale_conditions.settlement_type.get());
                checksum += bench::digest(message_2->original_trade.sale_conditions.trade_through_exempt_reason.get());
                checksum += bench::digest(message_2->original_trade.sale_conditions.extended_hours_or_sequence_type.get());
                checksum += bench::digest(message_2->original_trade.sale_conditions.sro_trade_detail.get());
                checksum += bench::digest(message_2->original_trade.trade_price.integer());
                checksum += bench::digest(message_2->original_trade.trade_volume.get());
                checksum += bench::digest(message_2->original_trade.sellers_sale_days.get());
                checksum += bench::digest(message_2->original_trade.stop_stock_indicator.get());
                checksum += bench::digest(message_2->original_trade.trade_through_exempt_indicator.get());
                checksum += bench::digest(message_2->original_trade.short_sale_restriction_indicator.get());
                checksum += bench::digest(message_2->original_trade.prior_day_trade_date_and_time.seconds.get());
                checksum += bench::digest(message_2->original_trade.prior_day_trade_date_and_time.nanoseconds.get());
                checksum += bench::digest(message_2->primary_listing_market_participant_id.get());
                checksum += bench::digest(message_2->financial_status_indicator.get());
                checksum += bench::digest(message_2->consolidated_data.previous_close_price_date.get());
                checksum += bench::digest(message_2->consolidated_data.last_participant_id.get());
                checksum += bench::digest(message_2->consolidated_data.last_price.integer());
                checksum += bench::digest(message_2->consolidated_data.high_price.integer());
                checksum += bench::digest(message_2->consolidated_data.low_price.integer());
                checksum += bench::digest(message_2->consolidated_data.total_volume_short.get());
                checksum += bench::digest(message_2->consolidated_data.tick.get());
                checksum += bench::digest(message_2->participant_data.previous_close_price_date.get());
                checksum += bench::digest(message_2->participant_data.last_price.integer());
                checksum += bench::digest(message_2->participant_data.high_price.integer());
                checksum += bench::digest(message_2->participant_data.low_price.integer());
                checksum += bench::digest(message_2->participant_data.open_price.integer());
                checksum += bench::digest(message_2->participant_data.total_volume_short.get());
                checksum += bench::digest(message_2->participant_data.tick.get());
            } else if (message->trade_message_type.get() == 'L') {
                [[maybe_unused]] const auto* message_2 = protocol::LongTradeMessage::parse(iterator.message + sizeof(protocol::TradeMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol.get());
                checksum += bench::digest(message_2->instrument_type.get());
                checksum += bench::digest(message_2->sale_conditions.settlement_type.get());
                checksum += bench::digest(message_2->sale_conditions.trade_through_exempt_reason.get());
                checksum += bench::digest(message_2->sale_conditions.extended_hours_or_sequence_type.get());
                checksum += bench::digest(message_2->sale_conditions.sro_trade_detail.get());
                checksum += bench::digest(message_2->trade_price.integer());
                checksum += bench::digest(message_2->trade_volume.get());
                checksum += bench::digest(message_2->sellers_sale_days.get());
                checksum += bench::digest(message_2->stop_stock_indicator.get());
                checksum += bench::digest(message_2->trade_through_exempt_indicator.get());
                checksum += bench::digest(message_2->trade_reporting_facility_id.get());
                checksum += bench::digest(message_2->timestamp_2.seconds.get());
                checksum += bench::digest(message_2->timestamp_2.nanoseconds.get());
                checksum += bench::digest(message_2->short_sale_restriction_indicator.get());
                checksum += bench::digest(message_2->primary_listing_market_participant_id.get());
                checksum += bench::digest(message_2->financial_status_indicator.get());
                checksum += bench::digest(message_2->held_trade_indicator.get());
                checksum += bench::digest(message_2->consolidated_high_low_last_indicator.get());
                checksum += bench::digest(message_2->participant_open_high_low_last_indicator.get());
            } else if (message->trade_message_type.get() == 'S') {
                [[maybe_unused]] const auto* message_2 = protocol::TradingStatusMessage::parse(iterator.message + sizeof(protocol::TradeMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol.get());
                checksum += bench::digest(message_2->instrument_type.get());
                checksum += bench::digest(message_2->last_price.integer());
                checksum += bench::digest(message_2->high_indication_price_upper_limit_price_band.integer());
                checksum += bench::digest(message_2->low_indication_price_lower_limit_price_band.integer());
                checksum += bench::digest(message_2->buy_volume.get());
                checksum += bench::digest(message_2->sell_volume.get());
                checksum += bench::digest(message_2->security_status.get());
                checksum += bench::digest(message_2->halt_reason.get());
                checksum += bench::digest(message_2->short_sale_restriction_indicator.get());
                checksum += bench::digest(message_2->primary_listing_market_participant_id.get());
                checksum += bench::digest(message_2->financial_status_indicator.get());
                checksum += bench::digest(message_2->limit_up_limit_down_indicator.get());
            } else if (message->trade_message_type.get() == 'T') {
                [[maybe_unused]] const auto* message_2 = protocol::ShortTradeMessage::parse(iterator.message + sizeof(protocol::TradeMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol_short.get());
                checksum += bench::digest(message_2->sale_condition.get());
                checksum += bench::digest(message_2->sale_condition_category.get());
                checksum += bench::digest(message_2->trade_price_short.integer());
                checksum += bench::digest(message_2->trade_volume_short.get());
                checksum += bench::digest(message_2->primary_listing_market_participant_id.get());
                checksum += bench::digest(message_2->consolidated_high_low_last_indicator.get());
                checksum += bench::digest(message_2->participant_open_high_low_last_indicator.get());
            } else if (message->trade_message_type.get() == 'X') {
                [[maybe_unused]] const auto* message_2 = protocol::TradeCancelErrorMessage::parse(iterator.message + sizeof(protocol::TradeMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->timestamp_1.seconds.get());
                checksum += bench::digest(message_2->timestamp_1.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol.get());
                checksum += bench::digest(message_2->instrument_type.get());
                checksum += bench::digest(message_2->sale_conditions.settlement_type.get());
                checksum += bench::digest(message_2->sale_conditions.trade_through_exempt_reason.get());
                checksum += bench::digest(message_2->sale_conditions.extended_hours_or_sequence_type.get());
                checksum += bench::digest(message_2->sale_conditions.sro_trade_detail.get());
                checksum += bench::digest(message_2->trade_price.integer());
                checksum += bench::digest(message_2->trade_volume.get());
                checksum += bench::digest(message_2->sellers_sale_days.get());
                checksum += bench::digest(message_2->stop_stock_indicator.get());
                checksum += bench::digest(message_2->trade_through_exempt_indicator.get());
                checksum += bench::digest(message_2->trade_reporting_facility_id.get());
                checksum += bench::digest(message_2->original_participant_reference_number.get());
                checksum += bench::digest(message_2->timestamp_2.seconds.get());
                checksum += bench::digest(message_2->timestamp_2.nanoseconds.get());
                checksum += bench::digest(message_2->cancel_error_action.get());
                checksum += bench::digest(message_2->short_sale_restriction_indicator.get());
                checksum += bench::digest(message_2->primary_listing_market_participant_id.get());
                checksum += bench::digest(message_2->financial_status_indicator.get());
                checksum += bench::digest(message_2->consolidated_data.previous_close_price_date.get());
                checksum += bench::digest(message_2->consolidated_data.last_participant_id.get());
                checksum += bench::digest(message_2->consolidated_data.last_price.integer());
                checksum += bench::digest(message_2->consolidated_data.high_price.integer());
                checksum += bench::digest(message_2->consolidated_data.low_price.integer());
                checksum += bench::digest(message_2->consolidated_data.total_volume_short.get());
                checksum += bench::digest(message_2->consolidated_data.tick.get());
                checksum += bench::digest(message_2->participant_data.previous_close_price_date.get());
                checksum += bench::digest(message_2->participant_data.last_price.integer());
                checksum += bench::digest(message_2->participant_data.high_price.integer());
                checksum += bench::digest(message_2->participant_data.low_price.integer());
                checksum += bench::digest(message_2->participant_data.open_price.integer());
                checksum += bench::digest(message_2->participant_data.total_volume_short.get());
                checksum += bench::digest(message_2->participant_data.tick.get());
            }
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Siac.Cts.Output.Cta.v2.9", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
