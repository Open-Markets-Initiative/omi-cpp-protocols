#pragma once

#include <ostream>
#include <string_view>

#include "StartOfEndOfDaySummaryMessage.hpp"
#include "EndOfEndOfDaySummaryMessage.hpp"
#include "StartOfStartOfDaySummaryMessage.hpp"
#include "EndOfStartOfDaySummaryMessage.hpp"
#include "SymbolReferenceDataMessage.hpp"
#include "StartOfDayMessage.hpp"
#include "ResetBlockSequenceNumberMessage.hpp"
#include "DisasterRecoveryDataCenterActivationMessage.hpp"
#include "LineIntegrityMessage.hpp"
#include "EndOfDayMessage.hpp"
#include "IndexMessage.hpp"
#include "BidAndOfferIndexMessage.hpp"
#include "MarketWideCircuitBreakerDeclineLevelStatusMessage.hpp"
#include "MarketWideCircuitBreakerStatusMessage.hpp"
#include "ApproximateAdjustedVolumeMarketCenterMessage.hpp"
#include "FractionalApproximateAdjustedVolumeMarketCenterMessage.hpp"
#include "ApproximateTradesAndTotalDollarValueMessage.hpp"
#include "CrossingSessionSummaryMessage.hpp"
#include "PriorDayTradeCorrectionMessage.hpp"
#include "PriorDayTradeMessage.hpp"
#include "PriorDayTradeCancelErrorMessage.hpp"
#include "FractionalPriorDayTradeCorrectionMessage.hpp"
#include "FractionalPriorDayTradeMessage.hpp"
#include "FractionalPriorDayTradeCancelErrorMessage.hpp"
#include "ConsolidatedStartOfDaySummaryMessage.hpp"
#include "ParticipantStartOfDaySummaryMessage.hpp"
#include "ConsolidatedEndOfDaySummaryMessage.hpp"
#include "FractionalConsolidatedEndOfDaySummaryMessage.hpp"
#include "ParticipantEndOfDaySummaryMessage.hpp"
#include "FractionalParticipantEndOfDaySummaryMessage.hpp"
#include "AuctionStatusMessage.hpp"
#include "TradeCorrectionMessage.hpp"
#include "LongTradeMessage.hpp"
#include "ShortTradeMessage.hpp"
#include "TradeCancelErrorMessage.hpp"
#include "FractionalTradeCorrectionMessage.hpp"
#include "FractionalLongTradeMessage.hpp"
#include "TradingStatusMessage.hpp"
#include "FractionalShortTradeMessage.hpp"
#include "FractionalTradeCancelErrorMessage.hpp"
#include "../json/messages/approximate_adjusted_volume_market_center_message_json.hpp"
#include "../json/messages/fractional_approximate_adjusted_volume_market_center_message_json.hpp"

namespace siac::cts::output::cta::v2_11_b {

namespace cta_output = ::siac::cts::output::cta::v2_11_b;

inline std::ostream& operator<<(std::ostream& os, const block_header& value) {
    os << "version=" << static_cast<unsigned>(value.version.get().value())
       << ",block_size=" << value.block_size.get().value()
       << ",data_feed_indicator=\"" << value.data_feed_indicator.get().value() << '"'
       << ",retransmission_indicator=\"" << value.retransmission_indicator.get().value() << '"'
       << ",block_sequence_number=" << value.block_sequence_number.get().value()
       << ",messages_in_block=" << static_cast<unsigned>(value.messages_in_block.get().value())
       << ",sip_block_timestamp.seconds=" << value.sip_block_timestamp.seconds.get().value()
       << ",sip_block_timestamp.nanoseconds=" << value.sip_block_timestamp.nanoseconds.get().value()
       << ",block_checksum=" << value.block_checksum.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message& value) {
    os << "message_length=" << value.message_length.get().value()
       << ",message_category=\"" << cta_output::message_category::to_string(value.message_category.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const administrative_message& value) {
    os << "administrative_message_type=\"" << cta_output::administrative_message_type::to_string(value.administrative_message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const sip_block_timestamp& value) {
    os << "seconds=" << value.seconds.get().value()
       << ",nanoseconds=" << value.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const timestamp_1& value) {
    os << "seconds=" << value.seconds.get().value()
       << ",nanoseconds=" << value.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const corrected_prior_day_trade_date_and_time& value) {
    os << "seconds=" << value.seconds.get().value()
       << ",nanoseconds=" << value.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const original_prior_day_trade_date_and_time& value) {
    os << "seconds=" << value.seconds.get().value()
       << ",nanoseconds=" << value.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const prior_day_trade_date_and_time& value) {
    os << "seconds=" << value.seconds.get().value()
       << ",nanoseconds=" << value.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const timestamp_2& value) {
    os << "seconds=" << value.seconds.get().value()
       << ",nanoseconds=" << value.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const start_of_end_of_day_summary_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const end_of_end_of_day_summary_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const start_of_start_of_day_summary_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const end_of_start_of_day_summary_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const symbol_reference_data_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",prior_security_symbol=\"" << msg.fields.prior_security_symbol.get_trimmed().value() << '"'
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",primary_listing_market_previous_closing_price=" << msg.fields.primary_listing_market_previous_closing_price.get().value()
       << ",consolidated_closing_price=" << msg.fields.consolidated_closing_price.get().value()
       << ",round_lot_size=" << msg.fields.round_lot_size.get().value()
       << ",minimum_price_increment_indicator=\"" << cta_output::minimum_price_increment_indicator::to_string(msg.fields.minimum_price_increment_indicator.get().value()) << '"'
       << ",luld_tier=\"" << cta_output::luld_tier::to_string(msg.fields.luld_tier.get().value()) << '"'
       << ",luld_leverage_ratio=" << msg.fields.luld_leverage_ratio.get().value()
       << ",test=\"" << cta_output::test::to_string(msg.fields.test.get().value()) << '"'
       << ",ipo=\"" << cta_output::ipo::to_string(msg.fields.ipo.get().value()) << '"'
       << ",financial_status_indicator=\"" << cta_output::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       << ",short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.short_sale_restriction_indicator.get().value()) << '"'
       << ",halt_reason=\"" << cta_output::halt_reason::to_string(msg.fields.halt_reason.get().value()) << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",second_reserved=\"" << msg.fields.second_reserved.get().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const start_of_day_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const reset_block_sequence_number_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const disaster_recovery_data_center_activation_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const line_integrity_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const end_of_day_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const index_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",index_symbol=\"" << msg.fields.index_symbol.get_trimmed().value() << '"'
       << ",index_value=" << msg.fields.index_value.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const bid_and_offer_index_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",index_symbol=\"" << msg.fields.index_symbol.get_trimmed().value() << '"'
       << ",bid_index_value=" << msg.fields.bid_index_value.get().value()
       << ",offer_index_value=" << msg.fields.offer_index_value.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const market_wide_circuit_breaker_decline_level_status_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",mwcb_level_1=" << msg.fields.mwcb_level_1.get().value()
       << ",mwcb_level_2=" << msg.fields.mwcb_level_2.get().value()
       << ",mwcb_level_3=" << msg.fields.mwcb_level_3.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const market_wide_circuit_breaker_status_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",market_wide_circuit_breaker_level_indicator=\"" << cta_output::market_wide_circuit_breaker_level_indicator::to_string(msg.fields.market_wide_circuit_breaker_level_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const approximate_adjusted_volume_market_center_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",number_of_participants=" << static_cast<unsigned>(msg.fields.number_of_participants.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const fractional_approximate_adjusted_volume_market_center_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",number_of_participants=" << static_cast<unsigned>(msg.fields.number_of_participants.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const approximate_trades_and_total_dollar_value_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",total_trades=" << msg.fields.total_trades.get().value()
       << ",dollar_value=" << msg.fields.dollar_value.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const crossing_session_summary_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",crossing_session_i_total_trades_volume=" << msg.fields.crossing_session_i_total_trades_volume.get().value()
       << ",crossing_session_ii_dollar_value=" << msg.fields.crossing_session_ii_dollar_value.get().value()
       << ",crossing_session_ii_total_trades_volume=" << msg.fields.crossing_session_ii_total_trades_volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const prior_day_trade_correction_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",corrected_sale_condition=\"" << msg.fields.corrected_sale_condition.get_trimmed().value() << '"'
       << ",corrected_trade_price=" << msg.fields.corrected_trade_price.get().value()
       << ",corrected_trade_volume=" << msg.fields.corrected_trade_volume.get().value()
       << ",corrected_sellers_sale_days=" << static_cast<unsigned>(msg.fields.corrected_sellers_sale_days.get().value())
       << ",corrected_stop_stock_indicator=\"" << msg.fields.corrected_stop_stock_indicator.get().value() << '"'
       << ",corrected_trade_through_exempt_indicator=\"" << msg.fields.corrected_trade_through_exempt_indicator.get().value() << '"'
       << ",corrected_short_sale_restriction_indicator=\"" << msg.fields.corrected_short_sale_restriction_indicator.get().value() << '"'
       << ",corrected_prior_day_trade_date_and_time.seconds=" << msg.fields.corrected_prior_day_trade_date_and_time.seconds.get().value()
       << ",corrected_prior_day_trade_date_and_time.nanoseconds=" << msg.fields.corrected_prior_day_trade_date_and_time.nanoseconds.get().value()
       << ",trade_reporting_facility_id=\"" << cta_output::trade_reporting_facility_id::to_string(msg.fields.trade_reporting_facility_id.get().value()) << '"'
       << ",original_sale_condition=\"" << msg.fields.original_sale_condition.get_trimmed().value() << '"'
       << ",original_trade_price=" << msg.fields.original_trade_price.get().value()
       << ",original_trade_volume=" << msg.fields.original_trade_volume.get().value()
       << ",original_sellers_sale_days=" << static_cast<unsigned>(msg.fields.original_sellers_sale_days.get().value())
       << ",original_stop_stock_indicator=\"" << msg.fields.original_stop_stock_indicator.get().value() << '"'
       << ",original_trade_through_exempt_indicator=\"" << msg.fields.original_trade_through_exempt_indicator.get().value() << '"'
       << ",original_short_sale_restriction_indicator=\"" << msg.fields.original_short_sale_restriction_indicator.get().value() << '"'
       << ",original_prior_day_trade_date_and_time.seconds=" << msg.fields.original_prior_day_trade_date_and_time.seconds.get().value()
       << ",original_prior_day_trade_date_and_time.nanoseconds=" << msg.fields.original_prior_day_trade_date_and_time.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const prior_day_trade_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",sale_condition_4.category_1=\"" << cta_output::category_1::to_string(msg.fields.sale_condition_4.category_1.get().value()) << '"'
       << ",sale_condition_4.category_2=\"" << cta_output::category_2::to_string(msg.fields.sale_condition_4.category_2.get().value()) << '"'
       << ",sale_condition_4.category_3=\"" << cta_output::category_3::to_string(msg.fields.sale_condition_4.category_3.get().value()) << '"'
       << ",sale_condition_4.category_4=\"" << cta_output::category_4::to_string(msg.fields.sale_condition_4.category_4.get().value()) << '"'
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",trade_volume=" << msg.fields.trade_volume.get().value()
       << ",sellers_sale_days=" << static_cast<unsigned>(msg.fields.sellers_sale_days.get().value())
       << ",stop_stock_indicator=\"" << cta_output::stop_stock_indicator::to_string(msg.fields.stop_stock_indicator.get().value()) << '"'
       << ",trade_through_exempt_indicator=\"" << cta_output::trade_through_exempt_indicator::to_string(msg.fields.trade_through_exempt_indicator.get().value()) << '"'
       << ",short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.short_sale_restriction_indicator.get().value()) << '"'
       << ",trade_reporting_facility_id=\"" << cta_output::trade_reporting_facility_id::to_string(msg.fields.trade_reporting_facility_id.get().value()) << '"'
       << ",prior_day_trade_date_and_time.seconds=" << msg.fields.prior_day_trade_date_and_time.seconds.get().value()
       << ",prior_day_trade_date_and_time.nanoseconds=" << msg.fields.prior_day_trade_date_and_time.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const prior_day_trade_cancel_error_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",sale_condition_4.category_1=\"" << cta_output::category_1::to_string(msg.fields.sale_condition_4.category_1.get().value()) << '"'
       << ",sale_condition_4.category_2=\"" << cta_output::category_2::to_string(msg.fields.sale_condition_4.category_2.get().value()) << '"'
       << ",sale_condition_4.category_3=\"" << cta_output::category_3::to_string(msg.fields.sale_condition_4.category_3.get().value()) << '"'
       << ",sale_condition_4.category_4=\"" << cta_output::category_4::to_string(msg.fields.sale_condition_4.category_4.get().value()) << '"'
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",trade_volume=" << msg.fields.trade_volume.get().value()
       << ",sellers_sale_days=" << static_cast<unsigned>(msg.fields.sellers_sale_days.get().value())
       << ",stop_stock_indicator=\"" << cta_output::stop_stock_indicator::to_string(msg.fields.stop_stock_indicator.get().value()) << '"'
       << ",trade_through_exempt_indicator=\"" << cta_output::trade_through_exempt_indicator::to_string(msg.fields.trade_through_exempt_indicator.get().value()) << '"'
       << ",short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.short_sale_restriction_indicator.get().value()) << '"'
       << ",trade_reporting_facility_id=\"" << cta_output::trade_reporting_facility_id::to_string(msg.fields.trade_reporting_facility_id.get().value()) << '"'
       << ",prior_day_trade_date_and_time.seconds=" << msg.fields.prior_day_trade_date_and_time.seconds.get().value()
       << ",prior_day_trade_date_and_time.nanoseconds=" << msg.fields.prior_day_trade_date_and_time.nanoseconds.get().value()
       << ",cancel_error_action=\"" << cta_output::cancel_error_action::to_string(msg.fields.cancel_error_action.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const fractional_prior_day_trade_correction_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",sale_condition_4.category_1=\"" << cta_output::category_1::to_string(msg.fields.sale_condition_4.category_1.get().value()) << '"'
       << ",sale_condition_4.category_2=\"" << cta_output::category_2::to_string(msg.fields.sale_condition_4.category_2.get().value()) << '"'
       << ",sale_condition_4.category_3=\"" << cta_output::category_3::to_string(msg.fields.sale_condition_4.category_3.get().value()) << '"'
       << ",sale_condition_4.category_4=\"" << cta_output::category_4::to_string(msg.fields.sale_condition_4.category_4.get().value()) << '"'
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",fractional_trade_volume=" << msg.fields.fractional_trade_volume.get().value()
       << ",sellers_sale_days=" << static_cast<unsigned>(msg.fields.sellers_sale_days.get().value())
       << ",stop_stock_indicator=\"" << cta_output::stop_stock_indicator::to_string(msg.fields.stop_stock_indicator.get().value()) << '"'
       << ",trade_through_exempt_indicator=\"" << cta_output::trade_through_exempt_indicator::to_string(msg.fields.trade_through_exempt_indicator.get().value()) << '"'
       << ",short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.short_sale_restriction_indicator.get().value()) << '"'
       << ",trade_reporting_facility_id=\"" << cta_output::trade_reporting_facility_id::to_string(msg.fields.trade_reporting_facility_id.get().value()) << '"'
       << ",prior_day_trade_date_and_time.seconds=" << msg.fields.prior_day_trade_date_and_time.seconds.get().value()
       << ",prior_day_trade_date_and_time.nanoseconds=" << msg.fields.prior_day_trade_date_and_time.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const fractional_prior_day_trade_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",sale_condition_4.category_1=\"" << cta_output::category_1::to_string(msg.fields.sale_condition_4.category_1.get().value()) << '"'
       << ",sale_condition_4.category_2=\"" << cta_output::category_2::to_string(msg.fields.sale_condition_4.category_2.get().value()) << '"'
       << ",sale_condition_4.category_3=\"" << cta_output::category_3::to_string(msg.fields.sale_condition_4.category_3.get().value()) << '"'
       << ",sale_condition_4.category_4=\"" << cta_output::category_4::to_string(msg.fields.sale_condition_4.category_4.get().value()) << '"'
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",fractional_trade_volume=" << msg.fields.fractional_trade_volume.get().value()
       << ",sellers_sale_days=" << static_cast<unsigned>(msg.fields.sellers_sale_days.get().value())
       << ",stop_stock_indicator=\"" << cta_output::stop_stock_indicator::to_string(msg.fields.stop_stock_indicator.get().value()) << '"'
       << ",trade_through_exempt_indicator=\"" << cta_output::trade_through_exempt_indicator::to_string(msg.fields.trade_through_exempt_indicator.get().value()) << '"'
       << ",short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.short_sale_restriction_indicator.get().value()) << '"'
       << ",trade_reporting_facility_id=\"" << cta_output::trade_reporting_facility_id::to_string(msg.fields.trade_reporting_facility_id.get().value()) << '"'
       << ",prior_day_trade_date_and_time.seconds=" << msg.fields.prior_day_trade_date_and_time.seconds.get().value()
       << ",prior_day_trade_date_and_time.nanoseconds=" << msg.fields.prior_day_trade_date_and_time.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const fractional_prior_day_trade_cancel_error_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",sale_condition_4.category_1=\"" << cta_output::category_1::to_string(msg.fields.sale_condition_4.category_1.get().value()) << '"'
       << ",sale_condition_4.category_2=\"" << cta_output::category_2::to_string(msg.fields.sale_condition_4.category_2.get().value()) << '"'
       << ",sale_condition_4.category_3=\"" << cta_output::category_3::to_string(msg.fields.sale_condition_4.category_3.get().value()) << '"'
       << ",sale_condition_4.category_4=\"" << cta_output::category_4::to_string(msg.fields.sale_condition_4.category_4.get().value()) << '"'
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",fractional_trade_volume=" << msg.fields.fractional_trade_volume.get().value()
       << ",sellers_sale_days=" << static_cast<unsigned>(msg.fields.sellers_sale_days.get().value())
       << ",stop_stock_indicator=\"" << cta_output::stop_stock_indicator::to_string(msg.fields.stop_stock_indicator.get().value()) << '"'
       << ",trade_through_exempt_indicator=\"" << cta_output::trade_through_exempt_indicator::to_string(msg.fields.trade_through_exempt_indicator.get().value()) << '"'
       << ",short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.short_sale_restriction_indicator.get().value()) << '"'
       << ",trade_reporting_facility_id=\"" << cta_output::trade_reporting_facility_id::to_string(msg.fields.trade_reporting_facility_id.get().value()) << '"'
       << ",prior_day_trade_date_and_time.seconds=" << msg.fields.prior_day_trade_date_and_time.seconds.get().value()
       << ",prior_day_trade_date_and_time.nanoseconds=" << msg.fields.prior_day_trade_date_and_time.nanoseconds.get().value()
       << ",cancel_error_action=\"" << cta_output::cancel_error_action::to_string(msg.fields.cancel_error_action.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const consolidated_start_of_day_summary_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",summary_participant_id=\"" << msg.fields.summary_participant_id.get().value() << '"'
       << ",previous_close_price_date=" << msg.fields.previous_close_price_date.get().value()
       << ",previous_close_price=" << msg.fields.previous_close_price.get().value()
       << ",short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.short_sale_restriction_indicator.get().value()) << '"'
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",financial_status_indicator=\"" << cta_output::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       << ",number_of_participants=" << static_cast<unsigned>(msg.fields.number_of_participants.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const participant_start_of_day_summary_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",summary_participant_id=\"" << msg.fields.summary_participant_id.get().value() << '"'
       << ",previous_close_price_date=" << msg.fields.previous_close_price_date.get().value()
       << ",previous_close_price=" << msg.fields.previous_close_price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const consolidated_end_of_day_summary_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",last_participant_id=\"" << msg.fields.last_participant_id.get().value() << '"'
       << ",previous_close_price_date=" << msg.fields.previous_close_price_date.get().value()
       << ",last_price=" << msg.fields.last_price.get().value()
       << ",high_price=" << msg.fields.high_price.get().value()
       << ",low_price=" << msg.fields.low_price.get().value()
       << ",total_volume=" << msg.fields.total_volume.get().value()
       << ",short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.short_sale_restriction_indicator.get().value()) << '"'
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",financial_status_indicator=\"" << cta_output::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       << ",number_of_participants=" << static_cast<unsigned>(msg.fields.number_of_participants.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const fractional_consolidated_end_of_day_summary_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",last_participant_id=\"" << msg.fields.last_participant_id.get().value() << '"'
       << ",previous_close_price_date=" << msg.fields.previous_close_price_date.get().value()
       << ",last_price=" << msg.fields.last_price.get().value()
       << ",high_price=" << msg.fields.high_price.get().value()
       << ",low_price=" << msg.fields.low_price.get().value()
       << ",fractional_total_volume=" << msg.fields.fractional_total_volume.get().value()
       << ",short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.short_sale_restriction_indicator.get().value()) << '"'
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",financial_status_indicator=\"" << cta_output::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       << ",number_of_participants=" << static_cast<unsigned>(msg.fields.number_of_participants.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const participant_end_of_day_summary_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",summary_participant_id=\"" << msg.fields.summary_participant_id.get().value() << '"'
       << ",previous_close_price_date=" << msg.fields.previous_close_price_date.get().value()
       << ",last_price=" << msg.fields.last_price.get().value()
       << ",high_price=" << msg.fields.high_price.get().value()
       << ",low_price=" << msg.fields.low_price.get().value()
       << ",open_price=" << msg.fields.open_price.get().value()
       << ",total_volume=" << msg.fields.total_volume.get().value()
       << ",tick=\"" << cta_output::tick::to_string(msg.fields.tick.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const fractional_participant_end_of_day_summary_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",summary_participant_id=\"" << msg.fields.summary_participant_id.get().value() << '"'
       << ",previous_close_price_date=" << msg.fields.previous_close_price_date.get().value()
       << ",last_price=" << msg.fields.last_price.get().value()
       << ",high_price=" << msg.fields.high_price.get().value()
       << ",low_price=" << msg.fields.low_price.get().value()
       << ",open_price=" << msg.fields.open_price.get().value()
       << ",fractional_total_volume=" << msg.fields.fractional_total_volume.get().value()
       << ",tick=\"" << cta_output::tick::to_string(msg.fields.tick.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_status_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",auction_collar_reference_price=" << msg.fields.auction_collar_reference_price.get().value()
       << ",auction_collar_upper_threshold_price=" << msg.fields.auction_collar_upper_threshold_price.get().value()
       << ",auction_collar_lower_threshold_price=" << msg.fields.auction_collar_lower_threshold_price.get().value()
       << ",number_of_extensions=" << static_cast<unsigned>(msg.fields.number_of_extensions.get().value())
       << ",short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.short_sale_restriction_indicator.get().value()) << '"'
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",financial_status_indicator=\"" << cta_output::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_correction_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",corrected_sale_condition=\"" << msg.fields.corrected_sale_condition.get_trimmed().value() << '"'
       << ",corrected_trade_price=" << msg.fields.corrected_trade_price.get().value()
       << ",corrected_trade_volume=" << msg.fields.corrected_trade_volume.get().value()
       << ",corrected_sellers_sale_days=" << static_cast<unsigned>(msg.fields.corrected_sellers_sale_days.get().value())
       << ",corrected_stop_stock_indicator=\"" << msg.fields.corrected_stop_stock_indicator.get().value() << '"'
       << ",corrected_trade_through_exempt_indicator=\"" << msg.fields.corrected_trade_through_exempt_indicator.get().value() << '"'
       << ",corrected_short_sale_restriction_indicator=\"" << msg.fields.corrected_short_sale_restriction_indicator.get().value() << '"'
       << ",trade_reporting_facility_id=\"" << cta_output::trade_reporting_facility_id::to_string(msg.fields.trade_reporting_facility_id.get().value()) << '"'
       << ",timestamp_2=" << (msg.fields.timestamp_2.get().has_value() ? std::to_string(msg.fields.timestamp_2.get().value()) : std::string_view("null"))
       << ",original_participant_reference_number=" << msg.fields.original_participant_reference_number.get().value()
       << ",original_sale_condition=\"" << msg.fields.original_sale_condition.get_trimmed().value() << '"'
       << ",original_trade_price=" << msg.fields.original_trade_price.get().value()
       << ",original_trade_volume=" << msg.fields.original_trade_volume.get().value()
       << ",original_sellers_sale_days=" << static_cast<unsigned>(msg.fields.original_sellers_sale_days.get().value())
       << ",original_stop_stock_indicator=\"" << msg.fields.original_stop_stock_indicator.get().value() << '"'
       << ",original_trade_through_exempt_indicator=\"" << msg.fields.original_trade_through_exempt_indicator.get().value() << '"'
       << ",original_short_sale_restriction_indicator=\"" << msg.fields.original_short_sale_restriction_indicator.get().value() << '"'
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",financial_status_indicator=\"" << cta_output::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       << ",consolidated_previous_close_price_date=" << msg.fields.consolidated_previous_close_price_date.get().value()
       << ",consolidated_last_participant_id=\"" << msg.fields.consolidated_last_participant_id.get().value() << '"'
       << ",consolidated_last_price=" << msg.fields.consolidated_last_price.get().value()
       << ",consolidated_high_price=" << msg.fields.consolidated_high_price.get().value()
       << ",consolidated_low_price=" << msg.fields.consolidated_low_price.get().value()
       << ",consolidated_total_volume=" << msg.fields.consolidated_total_volume.get().value()
       << ",consolidated_tick=\"" << msg.fields.consolidated_tick.get().value() << '"'
       << ",participant_previous_close_price_date=" << msg.fields.participant_previous_close_price_date.get().value()
       << ",participant_last_price=" << msg.fields.participant_last_price.get().value()
       << ",participant_high_price=" << msg.fields.participant_high_price.get().value()
       << ",participant_low_price=" << msg.fields.participant_low_price.get().value()
       << ",participant_open_price=" << msg.fields.participant_open_price.get().value()
       << ",participant_total_volume=" << msg.fields.participant_total_volume.get().value()
       << ",participant_tick=\"" << msg.fields.participant_tick.get().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const long_trade_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",sale_condition_4.category_1=\"" << cta_output::category_1::to_string(msg.fields.sale_condition_4.category_1.get().value()) << '"'
       << ",sale_condition_4.category_2=\"" << cta_output::category_2::to_string(msg.fields.sale_condition_4.category_2.get().value()) << '"'
       << ",sale_condition_4.category_3=\"" << cta_output::category_3::to_string(msg.fields.sale_condition_4.category_3.get().value()) << '"'
       << ",sale_condition_4.category_4=\"" << cta_output::category_4::to_string(msg.fields.sale_condition_4.category_4.get().value()) << '"'
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",trade_volume=" << msg.fields.trade_volume.get().value()
       << ",sellers_sale_days=" << static_cast<unsigned>(msg.fields.sellers_sale_days.get().value())
       << ",stop_stock_indicator=\"" << cta_output::stop_stock_indicator::to_string(msg.fields.stop_stock_indicator.get().value()) << '"'
       << ",trade_through_exempt_indicator=\"" << cta_output::trade_through_exempt_indicator::to_string(msg.fields.trade_through_exempt_indicator.get().value()) << '"'
       << ",trade_reporting_facility_id=\"" << cta_output::trade_reporting_facility_id::to_string(msg.fields.trade_reporting_facility_id.get().value()) << '"'
       << ",timestamp_2=" << (msg.fields.timestamp_2.get().has_value() ? std::to_string(msg.fields.timestamp_2.get().value()) : std::string_view("null"))
       << ",short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.short_sale_restriction_indicator.get().value()) << '"'
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",financial_status_indicator=\"" << cta_output::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       << ",held_trade_indicator=\"" << cta_output::held_trade_indicator::to_string(msg.fields.held_trade_indicator.get().value()) << '"'
       << ",consolidated_high_low_last_indicator=\"" << cta_output::consolidated_high_low_last_indicator::to_string(msg.fields.consolidated_high_low_last_indicator.get().value()) << '"'
       << ",participant_open_high_low_last_indicator=\"" << cta_output::participant_open_high_low_last_indicator::to_string(msg.fields.participant_open_high_low_last_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const short_trade_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol_5=\"" << msg.fields.security_symbol_5.get_trimmed().value() << '"'
       << ",sale_condition_1=\"" << cta_output::sale_condition_1::to_string(msg.fields.sale_condition_1.get().value()) << '"'
       << ",sale_condition_category=\"" << cta_output::sale_condition_category::to_string(msg.fields.sale_condition_category.get().value()) << '"'
       << ",trade_price_2=" << msg.fields.trade_price_2.get().value()
       << ",trade_volume_2=" << msg.fields.trade_volume_2.get().value()
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",consolidated_high_low_last_indicator=\"" << cta_output::consolidated_high_low_last_indicator::to_string(msg.fields.consolidated_high_low_last_indicator.get().value()) << '"'
       << ",participant_open_high_low_last_indicator=\"" << cta_output::participant_open_high_low_last_indicator::to_string(msg.fields.participant_open_high_low_last_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_cancel_error_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",sale_condition_4.category_1=\"" << cta_output::category_1::to_string(msg.fields.sale_condition_4.category_1.get().value()) << '"'
       << ",sale_condition_4.category_2=\"" << cta_output::category_2::to_string(msg.fields.sale_condition_4.category_2.get().value()) << '"'
       << ",sale_condition_4.category_3=\"" << cta_output::category_3::to_string(msg.fields.sale_condition_4.category_3.get().value()) << '"'
       << ",sale_condition_4.category_4=\"" << cta_output::category_4::to_string(msg.fields.sale_condition_4.category_4.get().value()) << '"'
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",trade_volume=" << msg.fields.trade_volume.get().value()
       << ",sellers_sale_days=" << static_cast<unsigned>(msg.fields.sellers_sale_days.get().value())
       << ",stop_stock_indicator=\"" << cta_output::stop_stock_indicator::to_string(msg.fields.stop_stock_indicator.get().value()) << '"'
       << ",trade_through_exempt_indicator=\"" << cta_output::trade_through_exempt_indicator::to_string(msg.fields.trade_through_exempt_indicator.get().value()) << '"'
       << ",trade_reporting_facility_id=\"" << cta_output::trade_reporting_facility_id::to_string(msg.fields.trade_reporting_facility_id.get().value()) << '"'
       << ",original_participant_reference_number=" << msg.fields.original_participant_reference_number.get().value()
       << ",timestamp_2=" << (msg.fields.timestamp_2.get().has_value() ? std::to_string(msg.fields.timestamp_2.get().value()) : std::string_view("null"))
       << ",cancel_error_action=\"" << cta_output::cancel_error_action::to_string(msg.fields.cancel_error_action.get().value()) << '"'
       << ",short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.short_sale_restriction_indicator.get().value()) << '"'
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",financial_status_indicator=\"" << cta_output::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       << ",consolidated_previous_close_price_date=" << msg.fields.consolidated_previous_close_price_date.get().value()
       << ",consolidated_last_participant_id=\"" << msg.fields.consolidated_last_participant_id.get().value() << '"'
       << ",consolidated_last_price=" << msg.fields.consolidated_last_price.get().value()
       << ",consolidated_high_price=" << msg.fields.consolidated_high_price.get().value()
       << ",consolidated_low_price=" << msg.fields.consolidated_low_price.get().value()
       << ",consolidated_total_volume=" << msg.fields.consolidated_total_volume.get().value()
       << ",consolidated_tick=\"" << msg.fields.consolidated_tick.get().value() << '"'
       << ",participant_previous_close_price_date=" << msg.fields.participant_previous_close_price_date.get().value()
       << ",participant_last_price=" << msg.fields.participant_last_price.get().value()
       << ",participant_high_price=" << msg.fields.participant_high_price.get().value()
       << ",participant_low_price=" << msg.fields.participant_low_price.get().value()
       << ",participant_open_price=" << msg.fields.participant_open_price.get().value()
       << ",participant_total_volume=" << msg.fields.participant_total_volume.get().value()
       << ",participant_tick=\"" << msg.fields.participant_tick.get().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const fractional_trade_correction_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",corrected_sale_condition=\"" << msg.fields.corrected_sale_condition.get_trimmed().value() << '"'
       << ",corrected_trade_price=" << msg.fields.corrected_trade_price.get().value()
       << ",corrected_fractional_trade_volume=" << msg.fields.corrected_fractional_trade_volume.get().value()
       << ",corrected_sellers_sale_days=" << static_cast<unsigned>(msg.fields.corrected_sellers_sale_days.get().value())
       << ",corrected_stop_stock_indicator=\"" << msg.fields.corrected_stop_stock_indicator.get().value() << '"'
       << ",corrected_trade_through_exempt_indicator=\"" << msg.fields.corrected_trade_through_exempt_indicator.get().value() << '"'
       << ",corrected_short_sale_restriction_indicator=\"" << msg.fields.corrected_short_sale_restriction_indicator.get().value() << '"'
       << ",trade_reporting_facility_id=\"" << cta_output::trade_reporting_facility_id::to_string(msg.fields.trade_reporting_facility_id.get().value()) << '"'
       << ",timestamp_2=" << (msg.fields.timestamp_2.get().has_value() ? std::to_string(msg.fields.timestamp_2.get().value()) : std::string_view("null"))
       << ",original_participant_reference_number=" << msg.fields.original_participant_reference_number.get().value()
       << ",original_sale_condition=\"" << msg.fields.original_sale_condition.get_trimmed().value() << '"'
       << ",original_trade_price=" << msg.fields.original_trade_price.get().value()
       << ",original_fractional_trade_volume=" << msg.fields.original_fractional_trade_volume.get().value()
       << ",original_sellers_sale_days=" << static_cast<unsigned>(msg.fields.original_sellers_sale_days.get().value())
       << ",original_stop_stock_indicator=\"" << msg.fields.original_stop_stock_indicator.get().value() << '"'
       << ",original_trade_through_exempt_indicator=\"" << msg.fields.original_trade_through_exempt_indicator.get().value() << '"'
       << ",original_short_sale_restriction_indicator=\"" << msg.fields.original_short_sale_restriction_indicator.get().value() << '"'
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",financial_status_indicator=\"" << cta_output::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       << ",consolidated_previous_close_price_date=" << msg.fields.consolidated_previous_close_price_date.get().value()
       << ",consolidated_last_participant_id=\"" << msg.fields.consolidated_last_participant_id.get().value() << '"'
       << ",consolidated_last_price=" << msg.fields.consolidated_last_price.get().value()
       << ",consolidated_high_price=" << msg.fields.consolidated_high_price.get().value()
       << ",consolidated_low_price=" << msg.fields.consolidated_low_price.get().value()
       << ",consolidated_fractional_total_volume=" << msg.fields.consolidated_fractional_total_volume.get().value()
       << ",consolidated_tick=\"" << msg.fields.consolidated_tick.get().value() << '"'
       << ",participant_previous_close_price_date=" << msg.fields.participant_previous_close_price_date.get().value()
       << ",participant_last_price=" << msg.fields.participant_last_price.get().value()
       << ",participant_high_price=" << msg.fields.participant_high_price.get().value()
       << ",participant_low_price=" << msg.fields.participant_low_price.get().value()
       << ",participant_open_price=" << msg.fields.participant_open_price.get().value()
       << ",participant_fractional_total_volume=" << msg.fields.participant_fractional_total_volume.get().value()
       << ",participant_tick=\"" << msg.fields.participant_tick.get().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const fractional_long_trade_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",sale_condition_4.category_1=\"" << cta_output::category_1::to_string(msg.fields.sale_condition_4.category_1.get().value()) << '"'
       << ",sale_condition_4.category_2=\"" << cta_output::category_2::to_string(msg.fields.sale_condition_4.category_2.get().value()) << '"'
       << ",sale_condition_4.category_3=\"" << cta_output::category_3::to_string(msg.fields.sale_condition_4.category_3.get().value()) << '"'
       << ",sale_condition_4.category_4=\"" << cta_output::category_4::to_string(msg.fields.sale_condition_4.category_4.get().value()) << '"'
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",fractional_trade_volume=" << msg.fields.fractional_trade_volume.get().value()
       << ",sellers_sale_days=" << static_cast<unsigned>(msg.fields.sellers_sale_days.get().value())
       << ",stop_stock_indicator=\"" << cta_output::stop_stock_indicator::to_string(msg.fields.stop_stock_indicator.get().value()) << '"'
       << ",trade_through_exempt_indicator=\"" << cta_output::trade_through_exempt_indicator::to_string(msg.fields.trade_through_exempt_indicator.get().value()) << '"'
       << ",trade_reporting_facility_id=\"" << cta_output::trade_reporting_facility_id::to_string(msg.fields.trade_reporting_facility_id.get().value()) << '"'
       << ",timestamp_2=" << (msg.fields.timestamp_2.get().has_value() ? std::to_string(msg.fields.timestamp_2.get().value()) : std::string_view("null"))
       << ",short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.short_sale_restriction_indicator.get().value()) << '"'
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",financial_status_indicator=\"" << cta_output::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       << ",held_trade_indicator=\"" << cta_output::held_trade_indicator::to_string(msg.fields.held_trade_indicator.get().value()) << '"'
       << ",consolidated_high_low_last_indicator=\"" << cta_output::consolidated_high_low_last_indicator::to_string(msg.fields.consolidated_high_low_last_indicator.get().value()) << '"'
       << ",participant_open_high_low_last_indicator=\"" << cta_output::participant_open_high_low_last_indicator::to_string(msg.fields.participant_open_high_low_last_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trading_status_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",last_price=" << msg.fields.last_price.get().value()
       << ",high_indication_price_upper_limit_price_band=" << msg.fields.high_indication_price_upper_limit_price_band.get().value()
       << ",low_indication_price_lower_limit_price_band=" << msg.fields.low_indication_price_lower_limit_price_band.get().value()
       << ",buy_volume=" << msg.fields.buy_volume.get().value()
       << ",sell_volume=" << msg.fields.sell_volume.get().value()
       << ",security_status=\"" << cta_output::security_status::to_string(msg.fields.security_status.get().value()) << '"'
       << ",halt_reason=\"" << cta_output::halt_reason::to_string(msg.fields.halt_reason.get().value()) << '"'
       << ",short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.short_sale_restriction_indicator.get().value()) << '"'
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",financial_status_indicator=\"" << cta_output::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       << ",limit_up_limit_down_luld_indicator=\"" << cta_output::limit_up_limit_down_luld_indicator::to_string(msg.fields.limit_up_limit_down_luld_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const fractional_short_trade_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol_5=\"" << msg.fields.security_symbol_5.get_trimmed().value() << '"'
       << ",sale_condition_1=\"" << cta_output::sale_condition_1::to_string(msg.fields.sale_condition_1.get().value()) << '"'
       << ",sale_condition_category=\"" << cta_output::sale_condition_category::to_string(msg.fields.sale_condition_category.get().value()) << '"'
       << ",trade_price_2=" << msg.fields.trade_price_2.get().value()
       << ",fractional_trade_volume_4=" << msg.fields.fractional_trade_volume_4.get().value()
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",consolidated_high_low_last_indicator=\"" << cta_output::consolidated_high_low_last_indicator::to_string(msg.fields.consolidated_high_low_last_indicator.get().value()) << '"'
       << ",participant_open_high_low_last_indicator=\"" << cta_output::participant_open_high_low_last_indicator::to_string(msg.fields.participant_open_high_low_last_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const fractional_trade_cancel_error_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",sale_condition_4.category_1=\"" << cta_output::category_1::to_string(msg.fields.sale_condition_4.category_1.get().value()) << '"'
       << ",sale_condition_4.category_2=\"" << cta_output::category_2::to_string(msg.fields.sale_condition_4.category_2.get().value()) << '"'
       << ",sale_condition_4.category_3=\"" << cta_output::category_3::to_string(msg.fields.sale_condition_4.category_3.get().value()) << '"'
       << ",sale_condition_4.category_4=\"" << cta_output::category_4::to_string(msg.fields.sale_condition_4.category_4.get().value()) << '"'
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",fractional_trade_volume=" << msg.fields.fractional_trade_volume.get().value()
       << ",sellers_sale_days=" << static_cast<unsigned>(msg.fields.sellers_sale_days.get().value())
       << ",stop_stock_indicator=\"" << cta_output::stop_stock_indicator::to_string(msg.fields.stop_stock_indicator.get().value()) << '"'
       << ",trade_through_exempt_indicator=\"" << cta_output::trade_through_exempt_indicator::to_string(msg.fields.trade_through_exempt_indicator.get().value()) << '"'
       << ",trade_reporting_facility_id=\"" << cta_output::trade_reporting_facility_id::to_string(msg.fields.trade_reporting_facility_id.get().value()) << '"'
       << ",original_participant_reference_number=" << msg.fields.original_participant_reference_number.get().value()
       << ",timestamp_2=" << (msg.fields.timestamp_2.get().has_value() ? std::to_string(msg.fields.timestamp_2.get().value()) : std::string_view("null"))
       << ",cancel_error_action=\"" << cta_output::cancel_error_action::to_string(msg.fields.cancel_error_action.get().value()) << '"'
       << ",short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.short_sale_restriction_indicator.get().value()) << '"'
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",financial_status_indicator=\"" << cta_output::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       << ",consolidated_previous_close_price_date=" << msg.fields.consolidated_previous_close_price_date.get().value()
       << ",consolidated_last_participant_id=\"" << msg.fields.consolidated_last_participant_id.get().value() << '"'
       << ",consolidated_last_price=" << msg.fields.consolidated_last_price.get().value()
       << ",consolidated_high_price=" << msg.fields.consolidated_high_price.get().value()
       << ",consolidated_low_price=" << msg.fields.consolidated_low_price.get().value()
       << ",consolidated_fractional_total_volume=" << msg.fields.consolidated_fractional_total_volume.get().value()
       << ",consolidated_tick=\"" << msg.fields.consolidated_tick.get().value() << '"'
       << ",participant_previous_close_price_date=" << msg.fields.participant_previous_close_price_date.get().value()
       << ",participant_last_price=" << msg.fields.participant_last_price.get().value()
       << ",participant_high_price=" << msg.fields.participant_high_price.get().value()
       << ",participant_low_price=" << msg.fields.participant_low_price.get().value()
       << ",participant_open_price=" << msg.fields.participant_open_price.get().value()
       << ",participant_fractional_total_volume=" << msg.fields.participant_fractional_total_volume.get().value()
       << ",participant_tick=\"" << msg.fields.participant_tick.get().value() << '"'
       ;
    return os;
}

}
