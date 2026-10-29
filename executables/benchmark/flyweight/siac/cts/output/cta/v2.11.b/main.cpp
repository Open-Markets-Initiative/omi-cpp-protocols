// Siac.Cts.Output.Cta.v2.11.b benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/siac/cts/output/cta/v2.11.b.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/flyweight/siac/cts/output/cta/v2.11.b/definitions.hpp"

namespace protocol = ::siac::cts::output::cta::v2_11_b;

namespace {

// The messages Administrative Message Payload selects, their values set in the entry of the message holding it
struct AdministrativeMessagePayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::StartOfEndOfDaySummaryMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
    }

    void on(const protocol::EndOfEndOfDaySummaryMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
    }

    void on(const protocol::StartOfStartOfDaySummaryMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
    }

    void on(const protocol::EndOfStartOfDaySummaryMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
    }

    void on(const protocol::SymbolReferenceDataMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.prior_security_symbol());
        checksum += bench::digest(message.primary_listing_market_participant_id());
        checksum += bench::digest(message.primary_listing_market_previous_closing_price().mantissa());
        checksum += bench::digest(message.consolidated_closing_price().mantissa());
        checksum += bench::digest(message.round_lot_size());
        checksum += bench::digest(message.minimum_price_increment_indicator());
        checksum += bench::digest(message.luld_tier());
        checksum += bench::digest(message.luld_leverage_ratio().mantissa());
        checksum += bench::digest(message.test());
        checksum += bench::digest(message.ipo());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.short_sale_restriction_indicator());
        checksum += bench::digest(message.halt_reason());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.reserved());
        checksum += bench::digest(message.second_reserved());
        checksum += bench::digest(message.reserved_128());
    }
};

// The messages Control Message Payload selects, their values set in the entry of the message holding it
struct ControlMessagePayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::StartOfDayMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
    }

    void on(const protocol::ResetBlockSequenceNumberMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
    }

    void on(const protocol::DisasterRecoveryDataCenterActivationMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
    }

    void on(const protocol::LineIntegrityMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
    }

    void on(const protocol::EndOfDayMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
    }
};

// The messages Indices Message Payload selects, their values set in the entry of the message holding it
struct IndicesMessagePayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::IndexMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.index_symbol());
        checksum += bench::digest(message.index_value().mantissa());
    }

    void on(const protocol::BidAndOfferIndexMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.index_symbol());
        checksum += bench::digest(message.bid_index_value().mantissa());
        checksum += bench::digest(message.offer_index_value().mantissa());
    }
};

// The messages Market Status Message Payload selects, their values set in the entry of the message holding it
struct MarketStatusMessagePayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::MarketWideCircuitBreakerDeclineLevelStatusMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.mwcb_level_1().mantissa());
        checksum += bench::digest(message.mwcb_level_2().mantissa());
        checksum += bench::digest(message.mwcb_level_3().mantissa());
        checksum += bench::digest(message.reserved());
    }

    void on(const protocol::MarketWideCircuitBreakerStatusMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.market_wide_circuit_breaker_level_indicator());
        checksum += bench::digest(message.reserved());
    }

    void on(const protocol::ApproximateAdjustedVolumeMarketCenterMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.number_of_participants());
    }

    void on(const protocol::FractionalApproximateAdjustedVolumeMarketCenterMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.number_of_participants());
    }

    void on(const protocol::ApproximateTradesAndTotalDollarValueMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.total_trades());
        checksum += bench::digest(message.dollar_value().mantissa());
    }

    void on(const protocol::CrossingSessionSummaryMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.crossing_session_i_total_trades_volume());
        checksum += bench::digest(message.crossing_session_ii_dollar_value().mantissa());
        checksum += bench::digest(message.crossing_session_ii_total_trades_volume());
    }
};

// The messages Prior Day Message Payload selects, their values set in the entry of the message holding it
struct PriorDayMessagePayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::PriorDayTradeCorrectionMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.corrected_sale_condition());
        checksum += bench::digest(message.corrected_trade_price().mantissa());
        checksum += bench::digest(message.corrected_trade_volume());
        checksum += bench::digest(message.corrected_sellers_sale_days());
        checksum += bench::digest(message.corrected_stop_stock_indicator());
        checksum += bench::digest(message.corrected_trade_through_exempt_indicator());
        checksum += bench::digest(message.corrected_short_sale_restriction_indicator());
        checksum += bench::digest(message.corrected_prior_day_trade_date_and_time().seconds());
        checksum += bench::digest(message.corrected_prior_day_trade_date_and_time().nanoseconds());
        checksum += bench::digest(message.trade_reporting_facility_id());
        checksum += bench::digest(message.original_sale_condition());
        checksum += bench::digest(message.original_trade_price().mantissa());
        checksum += bench::digest(message.original_trade_volume());
        checksum += bench::digest(message.original_sellers_sale_days());
        checksum += bench::digest(message.original_stop_stock_indicator());
        checksum += bench::digest(message.original_trade_through_exempt_indicator());
        checksum += bench::digest(message.original_short_sale_restriction_indicator());
        checksum += bench::digest(message.original_prior_day_trade_date_and_time().seconds());
        checksum += bench::digest(message.original_prior_day_trade_date_and_time().nanoseconds());
    }

    void on(const protocol::PriorDayTradeMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.sale_condition_4().category_1());
        checksum += bench::digest(message.sale_condition_4().category_2());
        checksum += bench::digest(message.sale_condition_4().category_3());
        checksum += bench::digest(message.sale_condition_4().category_4());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.trade_volume());
        checksum += bench::digest(message.sellers_sale_days());
        checksum += bench::digest(message.stop_stock_indicator());
        checksum += bench::digest(message.trade_through_exempt_indicator());
        checksum += bench::digest(message.short_sale_restriction_indicator());
        checksum += bench::digest(message.trade_reporting_facility_id());
        checksum += bench::digest(message.prior_day_trade_date_and_time().seconds());
        checksum += bench::digest(message.prior_day_trade_date_and_time().nanoseconds());
    }

    void on(const protocol::PriorDayTradeCancelErrorMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.sale_condition_4().category_1());
        checksum += bench::digest(message.sale_condition_4().category_2());
        checksum += bench::digest(message.sale_condition_4().category_3());
        checksum += bench::digest(message.sale_condition_4().category_4());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.trade_volume());
        checksum += bench::digest(message.sellers_sale_days());
        checksum += bench::digest(message.stop_stock_indicator());
        checksum += bench::digest(message.trade_through_exempt_indicator());
        checksum += bench::digest(message.short_sale_restriction_indicator());
        checksum += bench::digest(message.trade_reporting_facility_id());
        checksum += bench::digest(message.prior_day_trade_date_and_time().seconds());
        checksum += bench::digest(message.prior_day_trade_date_and_time().nanoseconds());
        checksum += bench::digest(message.cancel_error_action());
    }

    void on(const protocol::FractionalPriorDayTradeCorrectionMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.sale_condition_4().category_1());
        checksum += bench::digest(message.sale_condition_4().category_2());
        checksum += bench::digest(message.sale_condition_4().category_3());
        checksum += bench::digest(message.sale_condition_4().category_4());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.fractional_trade_volume().mantissa());
        checksum += bench::digest(message.sellers_sale_days());
        checksum += bench::digest(message.stop_stock_indicator());
        checksum += bench::digest(message.trade_through_exempt_indicator());
        checksum += bench::digest(message.short_sale_restriction_indicator());
        checksum += bench::digest(message.trade_reporting_facility_id());
        checksum += bench::digest(message.prior_day_trade_date_and_time().seconds());
        checksum += bench::digest(message.prior_day_trade_date_and_time().nanoseconds());
    }

    void on(const protocol::FractionalPriorDayTradeMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.sale_condition_4().category_1());
        checksum += bench::digest(message.sale_condition_4().category_2());
        checksum += bench::digest(message.sale_condition_4().category_3());
        checksum += bench::digest(message.sale_condition_4().category_4());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.fractional_trade_volume().mantissa());
        checksum += bench::digest(message.sellers_sale_days());
        checksum += bench::digest(message.stop_stock_indicator());
        checksum += bench::digest(message.trade_through_exempt_indicator());
        checksum += bench::digest(message.short_sale_restriction_indicator());
        checksum += bench::digest(message.trade_reporting_facility_id());
        checksum += bench::digest(message.prior_day_trade_date_and_time().seconds());
        checksum += bench::digest(message.prior_day_trade_date_and_time().nanoseconds());
    }

    void on(const protocol::FractionalPriorDayTradeCancelErrorMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.sale_condition_4().category_1());
        checksum += bench::digest(message.sale_condition_4().category_2());
        checksum += bench::digest(message.sale_condition_4().category_3());
        checksum += bench::digest(message.sale_condition_4().category_4());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.fractional_trade_volume().mantissa());
        checksum += bench::digest(message.sellers_sale_days());
        checksum += bench::digest(message.stop_stock_indicator());
        checksum += bench::digest(message.trade_through_exempt_indicator());
        checksum += bench::digest(message.short_sale_restriction_indicator());
        checksum += bench::digest(message.trade_reporting_facility_id());
        checksum += bench::digest(message.prior_day_trade_date_and_time().seconds());
        checksum += bench::digest(message.prior_day_trade_date_and_time().nanoseconds());
        checksum += bench::digest(message.cancel_error_action());
    }
};

// The messages Summary Message Payload selects, their values set in the entry of the message holding it
struct SummaryMessagePayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::ConsolidatedStartOfDaySummaryMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.summary_participant_id());
        checksum += bench::digest(message.previous_close_price_date());
        checksum += bench::digest(message.previous_close_price().mantissa());
        checksum += bench::digest(message.short_sale_restriction_indicator());
        checksum += bench::digest(message.primary_listing_market_participant_id());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.number_of_participants());
    }

    void on(const protocol::ParticipantStartOfDaySummaryMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.summary_participant_id());
        checksum += bench::digest(message.previous_close_price_date());
        checksum += bench::digest(message.previous_close_price().mantissa());
    }

    void on(const protocol::ConsolidatedEndOfDaySummaryMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.last_participant_id());
        checksum += bench::digest(message.previous_close_price_date());
        checksum += bench::digest(message.last_price().mantissa());
        checksum += bench::digest(message.high_price().mantissa());
        checksum += bench::digest(message.low_price().mantissa());
        checksum += bench::digest(message.total_volume());
        checksum += bench::digest(message.short_sale_restriction_indicator());
        checksum += bench::digest(message.primary_listing_market_participant_id());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.number_of_participants());
    }

    void on(const protocol::FractionalConsolidatedEndOfDaySummaryMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.last_participant_id());
        checksum += bench::digest(message.previous_close_price_date());
        checksum += bench::digest(message.last_price().mantissa());
        checksum += bench::digest(message.high_price().mantissa());
        checksum += bench::digest(message.low_price().mantissa());
        checksum += bench::digest(message.fractional_total_volume().mantissa());
        checksum += bench::digest(message.short_sale_restriction_indicator());
        checksum += bench::digest(message.primary_listing_market_participant_id());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.number_of_participants());
    }

    void on(const protocol::ParticipantEndOfDaySummaryMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.summary_participant_id());
        checksum += bench::digest(message.previous_close_price_date());
        checksum += bench::digest(message.last_price().mantissa());
        checksum += bench::digest(message.high_price().mantissa());
        checksum += bench::digest(message.low_price().mantissa());
        checksum += bench::digest(message.open_price().mantissa());
        checksum += bench::digest(message.total_volume());
        checksum += bench::digest(message.tick());
    }

    void on(const protocol::FractionalParticipantEndOfDaySummaryMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.summary_participant_id());
        checksum += bench::digest(message.previous_close_price_date());
        checksum += bench::digest(message.last_price().mantissa());
        checksum += bench::digest(message.high_price().mantissa());
        checksum += bench::digest(message.low_price().mantissa());
        checksum += bench::digest(message.open_price().mantissa());
        checksum += bench::digest(message.fractional_total_volume().mantissa());
        checksum += bench::digest(message.tick());
    }
};

// The messages Trade Message Payload selects, their values set in the entry of the message holding it
struct TradeMessagePayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::AuctionStatusMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.auction_collar_reference_price().mantissa());
        checksum += bench::digest(message.auction_collar_upper_threshold_price().mantissa());
        checksum += bench::digest(message.auction_collar_lower_threshold_price().mantissa());
        checksum += bench::digest(message.number_of_extensions());
        checksum += bench::digest(message.short_sale_restriction_indicator());
        checksum += bench::digest(message.primary_listing_market_participant_id());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.reserved_62());
    }

    void on(const protocol::TradeCorrectionMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.corrected_sale_condition());
        checksum += bench::digest(message.corrected_trade_price().mantissa());
        checksum += bench::digest(message.corrected_trade_volume());
        checksum += bench::digest(message.corrected_sellers_sale_days());
        checksum += bench::digest(message.corrected_stop_stock_indicator());
        checksum += bench::digest(message.corrected_trade_through_exempt_indicator());
        checksum += bench::digest(message.corrected_short_sale_restriction_indicator());
        checksum += bench::digest(message.trade_reporting_facility_id());
        checksum += bench::digest(message.timestamp_2().seconds());
        checksum += bench::digest(message.timestamp_2().nanoseconds());
        checksum += bench::digest(message.original_participant_reference_number());
        checksum += bench::digest(message.original_sale_condition());
        checksum += bench::digest(message.original_trade_price().mantissa());
        checksum += bench::digest(message.original_trade_volume());
        checksum += bench::digest(message.original_sellers_sale_days());
        checksum += bench::digest(message.original_stop_stock_indicator());
        checksum += bench::digest(message.original_trade_through_exempt_indicator());
        checksum += bench::digest(message.original_short_sale_restriction_indicator());
        checksum += bench::digest(message.primary_listing_market_participant_id());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.consolidated_previous_close_price_date());
        checksum += bench::digest(message.consolidated_last_participant_id());
        checksum += bench::digest(message.consolidated_last_price().mantissa());
        checksum += bench::digest(message.consolidated_high_price().mantissa());
        checksum += bench::digest(message.consolidated_low_price().mantissa());
        checksum += bench::digest(message.consolidated_total_volume());
        checksum += bench::digest(message.consolidated_tick());
        checksum += bench::digest(message.participant_previous_close_price_date());
        checksum += bench::digest(message.participant_last_price().mantissa());
        checksum += bench::digest(message.participant_high_price().mantissa());
        checksum += bench::digest(message.participant_low_price().mantissa());
        checksum += bench::digest(message.participant_open_price().mantissa());
        checksum += bench::digest(message.participant_total_volume());
        checksum += bench::digest(message.participant_tick());
    }

    void on(const protocol::LongTradeMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.sale_condition_4().category_1());
        checksum += bench::digest(message.sale_condition_4().category_2());
        checksum += bench::digest(message.sale_condition_4().category_3());
        checksum += bench::digest(message.sale_condition_4().category_4());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.trade_volume());
        checksum += bench::digest(message.sellers_sale_days());
        checksum += bench::digest(message.stop_stock_indicator());
        checksum += bench::digest(message.trade_through_exempt_indicator());
        checksum += bench::digest(message.trade_reporting_facility_id());
        checksum += bench::digest(message.timestamp_2().seconds());
        checksum += bench::digest(message.timestamp_2().nanoseconds());
        checksum += bench::digest(message.short_sale_restriction_indicator());
        checksum += bench::digest(message.primary_listing_market_participant_id());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.held_trade_indicator());
        checksum += bench::digest(message.consolidated_high_low_last_indicator());
        checksum += bench::digest(message.participant_open_high_low_last_indicator());
    }

    void on(const protocol::ShortTradeMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol_5());
        checksum += bench::digest(message.sale_condition_1());
        checksum += bench::digest(message.sale_condition_category());
        checksum += bench::digest(message.trade_price_2().mantissa());
        checksum += bench::digest(message.trade_volume_2());
        checksum += bench::digest(message.primary_listing_market_participant_id());
        checksum += bench::digest(message.consolidated_high_low_last_indicator());
        checksum += bench::digest(message.participant_open_high_low_last_indicator());
    }

    void on(const protocol::TradeCancelErrorMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.sale_condition_4().category_1());
        checksum += bench::digest(message.sale_condition_4().category_2());
        checksum += bench::digest(message.sale_condition_4().category_3());
        checksum += bench::digest(message.sale_condition_4().category_4());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.trade_volume());
        checksum += bench::digest(message.sellers_sale_days());
        checksum += bench::digest(message.stop_stock_indicator());
        checksum += bench::digest(message.trade_through_exempt_indicator());
        checksum += bench::digest(message.trade_reporting_facility_id());
        checksum += bench::digest(message.original_participant_reference_number());
        checksum += bench::digest(message.timestamp_2().seconds());
        checksum += bench::digest(message.timestamp_2().nanoseconds());
        checksum += bench::digest(message.cancel_error_action());
        checksum += bench::digest(message.short_sale_restriction_indicator());
        checksum += bench::digest(message.primary_listing_market_participant_id());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.consolidated_previous_close_price_date());
        checksum += bench::digest(message.consolidated_last_participant_id());
        checksum += bench::digest(message.consolidated_last_price().mantissa());
        checksum += bench::digest(message.consolidated_high_price().mantissa());
        checksum += bench::digest(message.consolidated_low_price().mantissa());
        checksum += bench::digest(message.consolidated_total_volume());
        checksum += bench::digest(message.consolidated_tick());
        checksum += bench::digest(message.participant_previous_close_price_date());
        checksum += bench::digest(message.participant_last_price().mantissa());
        checksum += bench::digest(message.participant_high_price().mantissa());
        checksum += bench::digest(message.participant_low_price().mantissa());
        checksum += bench::digest(message.participant_open_price().mantissa());
        checksum += bench::digest(message.participant_total_volume());
        checksum += bench::digest(message.participant_tick());
    }

    void on(const protocol::FractionalTradeCorrectionMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.corrected_sale_condition());
        checksum += bench::digest(message.corrected_trade_price().mantissa());
        checksum += bench::digest(message.corrected_fractional_trade_volume().mantissa());
        checksum += bench::digest(message.corrected_sellers_sale_days());
        checksum += bench::digest(message.corrected_stop_stock_indicator());
        checksum += bench::digest(message.corrected_trade_through_exempt_indicator());
        checksum += bench::digest(message.corrected_short_sale_restriction_indicator());
        checksum += bench::digest(message.trade_reporting_facility_id());
        checksum += bench::digest(message.timestamp_2().seconds());
        checksum += bench::digest(message.timestamp_2().nanoseconds());
        checksum += bench::digest(message.original_participant_reference_number());
        checksum += bench::digest(message.original_sale_condition());
        checksum += bench::digest(message.original_trade_price().mantissa());
        checksum += bench::digest(message.original_fractional_trade_volume().mantissa());
        checksum += bench::digest(message.original_sellers_sale_days());
        checksum += bench::digest(message.original_stop_stock_indicator());
        checksum += bench::digest(message.original_trade_through_exempt_indicator());
        checksum += bench::digest(message.original_short_sale_restriction_indicator());
        checksum += bench::digest(message.primary_listing_market_participant_id());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.consolidated_previous_close_price_date());
        checksum += bench::digest(message.consolidated_last_participant_id());
        checksum += bench::digest(message.consolidated_last_price().mantissa());
        checksum += bench::digest(message.consolidated_high_price().mantissa());
        checksum += bench::digest(message.consolidated_low_price().mantissa());
        checksum += bench::digest(message.consolidated_fractional_total_volume().mantissa());
        checksum += bench::digest(message.consolidated_tick());
        checksum += bench::digest(message.participant_previous_close_price_date());
        checksum += bench::digest(message.participant_last_price().mantissa());
        checksum += bench::digest(message.participant_high_price().mantissa());
        checksum += bench::digest(message.participant_low_price().mantissa());
        checksum += bench::digest(message.participant_open_price().mantissa());
        checksum += bench::digest(message.participant_fractional_total_volume().mantissa());
        checksum += bench::digest(message.participant_tick());
    }

    void on(const protocol::FractionalLongTradeMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.sale_condition_4().category_1());
        checksum += bench::digest(message.sale_condition_4().category_2());
        checksum += bench::digest(message.sale_condition_4().category_3());
        checksum += bench::digest(message.sale_condition_4().category_4());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.fractional_trade_volume().mantissa());
        checksum += bench::digest(message.sellers_sale_days());
        checksum += bench::digest(message.stop_stock_indicator());
        checksum += bench::digest(message.trade_through_exempt_indicator());
        checksum += bench::digest(message.trade_reporting_facility_id());
        checksum += bench::digest(message.timestamp_2().seconds());
        checksum += bench::digest(message.timestamp_2().nanoseconds());
        checksum += bench::digest(message.short_sale_restriction_indicator());
        checksum += bench::digest(message.primary_listing_market_participant_id());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.held_trade_indicator());
        checksum += bench::digest(message.consolidated_high_low_last_indicator());
        checksum += bench::digest(message.participant_open_high_low_last_indicator());
    }

    void on(const protocol::TradingStatusMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.last_price().mantissa());
        checksum += bench::digest(message.high_indication_price_upper_limit_price_band().mantissa());
        checksum += bench::digest(message.low_indication_price_lower_limit_price_band().mantissa());
        checksum += bench::digest(message.buy_volume());
        checksum += bench::digest(message.sell_volume());
        checksum += bench::digest(message.security_status());
        checksum += bench::digest(message.halt_reason());
        checksum += bench::digest(message.short_sale_restriction_indicator());
        checksum += bench::digest(message.primary_listing_market_participant_id());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.limit_up_limit_down_luld_indicator());
    }

    void on(const protocol::FractionalShortTradeMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol_5());
        checksum += bench::digest(message.sale_condition_1());
        checksum += bench::digest(message.sale_condition_category());
        checksum += bench::digest(message.trade_price_2().mantissa());
        checksum += bench::digest(message.fractional_trade_volume_4().mantissa());
        checksum += bench::digest(message.primary_listing_market_participant_id());
        checksum += bench::digest(message.consolidated_high_low_last_indicator());
        checksum += bench::digest(message.participant_open_high_low_last_indicator());
    }

    void on(const protocol::FractionalTradeCancelErrorMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.sale_condition_4().category_1());
        checksum += bench::digest(message.sale_condition_4().category_2());
        checksum += bench::digest(message.sale_condition_4().category_3());
        checksum += bench::digest(message.sale_condition_4().category_4());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.fractional_trade_volume().mantissa());
        checksum += bench::digest(message.sellers_sale_days());
        checksum += bench::digest(message.stop_stock_indicator());
        checksum += bench::digest(message.trade_through_exempt_indicator());
        checksum += bench::digest(message.trade_reporting_facility_id());
        checksum += bench::digest(message.original_participant_reference_number());
        checksum += bench::digest(message.timestamp_2().seconds());
        checksum += bench::digest(message.timestamp_2().nanoseconds());
        checksum += bench::digest(message.cancel_error_action());
        checksum += bench::digest(message.short_sale_restriction_indicator());
        checksum += bench::digest(message.primary_listing_market_participant_id());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.consolidated_previous_close_price_date());
        checksum += bench::digest(message.consolidated_last_participant_id());
        checksum += bench::digest(message.consolidated_last_price().mantissa());
        checksum += bench::digest(message.consolidated_high_price().mantissa());
        checksum += bench::digest(message.consolidated_low_price().mantissa());
        checksum += bench::digest(message.consolidated_fractional_total_volume().mantissa());
        checksum += bench::digest(message.consolidated_tick());
        checksum += bench::digest(message.participant_previous_close_price_date());
        checksum += bench::digest(message.participant_last_price().mantissa());
        checksum += bench::digest(message.participant_high_price().mantissa());
        checksum += bench::digest(message.participant_low_price().mantissa());
        checksum += bench::digest(message.participant_open_price().mantissa());
        checksum += bench::digest(message.participant_fractional_total_volume().mantissa());
        checksum += bench::digest(message.participant_tick());
    }
};

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.block_header().version());
        checksum += bench::digest(packet.block_header().block_size());
        checksum += bench::digest(packet.block_header().data_feed_indicator());
        checksum += bench::digest(packet.block_header().retransmission_indicator());
        checksum += bench::digest(packet.block_header().block_sequence_number());
        checksum += bench::digest(packet.block_header().messages_in_block());
        checksum += bench::digest(packet.block_header().sip_block_timestamp().seconds());
        checksum += bench::digest(packet.block_header().sip_block_timestamp().nanoseconds());
        checksum += bench::digest(packet.block_header().block_checksum());
    }

    // a message this test prints no values of, or a code no message answers to, still takes its entry
    template <typename Message>
    void on(const Message&) {
        ++index;
    }

    template <typename Code>
    void on_unknown(Code, std::span<const std::byte>) {
        ++index;
    }

    void on(const protocol::AdministrativeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.administrative_message_type());
        AdministrativeMessagePayloadHandler selected{ checksum };
        message.administrative_message_payload(selected);
    }

    void on(const protocol::ControlMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.control_message_type());
        ControlMessagePayloadHandler selected{ checksum };
        message.control_message_payload(selected);
    }

    void on(const protocol::IndicesMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.indices_message_type());
        IndicesMessagePayloadHandler selected{ checksum };
        message.indices_message_payload(selected);
    }

    void on(const protocol::MarketStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.market_status_message_type());
        MarketStatusMessagePayloadHandler selected{ checksum };
        message.market_status_message_payload(selected);
    }

    void on(const protocol::PriorDayMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.prior_day_message_type());
        PriorDayMessagePayloadHandler selected{ checksum };
        message.prior_day_message_payload(selected);
    }

    void on(const protocol::SummaryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.summary_message_type());
        SummaryMessagePayloadHandler selected{ checksum };
        message.summary_message_payload(selected);
    }

    void on(const protocol::TradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.trade_message_type());
        TradeMessagePayloadHandler selected{ checksum };
        message.trade_message_payload(selected);
    }
};

// The values the Flyweight reader reads from one datagram, folded into a checksum. A datagram it cannot
// read is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::PacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Siac.Cts.Output.Cta.v2.11.b", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
