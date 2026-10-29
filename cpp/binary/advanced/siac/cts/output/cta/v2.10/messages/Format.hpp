#pragma once

#include <ostream>
#include <string_view>

#include "StartOfEndOfDayMessage.hpp"
#include "EndOfEndOfDayMessage.hpp"
#include "StartOfStartOfDayMessage.hpp"
#include "EndOfStartOfDayMessage.hpp"
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
#include "FractionalPriorDayTradeCorrectionMessage.hpp"
#include "PriorDayTradeMessage.hpp"
#include "FractionalPriorDayTradeMessage.hpp"
#include "PriorDayTradeCancelErrorMessage.hpp"
#include "FractionalPriorDayTradeCancelErrorMessage.hpp"
#include "ConsolidatedStartOfDaySummaryMessage.hpp"
#include "ParticipantStartOfDaySummaryMessage.hpp"
#include "ConsolidatedEndOfDaySummaryMessage.hpp"
#include "FractionalConsolidatedEndOfDaySummaryMessage.hpp"
#include "ParticipantEndOfDaySummaryMessage.hpp"
#include "FractionalParticipantEndOfDaySummaryMessage.hpp"
#include "AuctionStatusMessage.hpp"
#include "TradeCorrectionMessage.hpp"
#include "FractionalTradeCorrectionMessage.hpp"
#include "LongTradeMessage.hpp"
#include "FractionalLongTradeMessage.hpp"
#include "TradingStatusMessage.hpp"
#include "ShortTradeMessage.hpp"
#include "FractionalShortTradeMessage.hpp"
#include "TradeCancelErrorMessage.hpp"
#include "FractionalTradeCancelErrorMessage.hpp"
#include "../json/messages/approximate_adjusted_volume_market_center_message_json.hpp"
#include "../json/messages/fractional_approximate_adjusted_volume_market_center_message_json.hpp"

namespace siac::cts::output::cta::v2_10 {

namespace cta_output = ::siac::cts::output::cta::v2_10;

inline std::ostream& operator<<(std::ostream& os, const block_header& value) {
    os << "version=" << static_cast<unsigned>(value.version.get().value())
       << ",block_size=" << value.block_size.get().value()
       << ",data_feed_indicator=\"" << value.data_feed_indicator.get().value() << '"'
       << ",retransmission_indicator=\"" << cta_output::retransmission_indicator::to_string(value.retransmission_indicator.get().value()) << '"'
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

inline std::ostream& operator<<(std::ostream& os, const start_of_end_of_day_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const end_of_end_of_day_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const start_of_start_of_day_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const end_of_start_of_day_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
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
       << ",prior_day_corrected_trade.sale_conditions.settlement_type=\"" << cta_output::settlement_type::to_string(msg.fields.prior_day_corrected_trade.sale_conditions.settlement_type.get().value()) << '"'
       << ",prior_day_corrected_trade.sale_conditions.trade_through_exempt_reason=\"" << cta_output::trade_through_exempt_reason::to_string(msg.fields.prior_day_corrected_trade.sale_conditions.trade_through_exempt_reason.get().value()) << '"'
       << ",prior_day_corrected_trade.sale_conditions.extended_hours_or_sequence_type=\"" << cta_output::extended_hours_or_sequence_type::to_string(msg.fields.prior_day_corrected_trade.sale_conditions.extended_hours_or_sequence_type.get().value()) << '"'
       << ",prior_day_corrected_trade.sale_conditions.sro_trade_detail=\"" << cta_output::sro_trade_detail::to_string(msg.fields.prior_day_corrected_trade.sale_conditions.sro_trade_detail.get().value()) << '"'
       << ",prior_day_corrected_trade.trade_price=" << msg.fields.prior_day_corrected_trade.trade_price.get().value()
       << ",prior_day_corrected_trade.trade_volume=" << msg.fields.prior_day_corrected_trade.trade_volume.get().value()
       << ",prior_day_corrected_trade.sellers_sale_days=" << static_cast<unsigned>(msg.fields.prior_day_corrected_trade.sellers_sale_days.get().value())
       << ",prior_day_corrected_trade.stop_stock_indicator=\"" << cta_output::stop_stock_indicator::to_string(msg.fields.prior_day_corrected_trade.stop_stock_indicator.get().value()) << '"'
       << ",prior_day_corrected_trade.trade_through_exempt_indicator=\"" << cta_output::trade_through_exempt_indicator::to_string(msg.fields.prior_day_corrected_trade.trade_through_exempt_indicator.get().value()) << '"'
       << ",prior_day_corrected_trade.short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.prior_day_corrected_trade.short_sale_restriction_indicator.get().value()) << '"'
       << ",prior_day_corrected_trade.prior_day_trade_date_and_time.seconds=" << msg.fields.prior_day_corrected_trade.prior_day_trade_date_and_time.seconds.get().value()
       << ",prior_day_corrected_trade.prior_day_trade_date_and_time.nanoseconds=" << msg.fields.prior_day_corrected_trade.prior_day_trade_date_and_time.nanoseconds.get().value()
       << ",trade_reporting_facility_id=\"" << cta_output::trade_reporting_facility_id::to_string(msg.fields.trade_reporting_facility_id.get().value()) << '"'
       << ",prior_day_original_trade.sale_conditions.settlement_type=\"" << cta_output::settlement_type::to_string(msg.fields.prior_day_original_trade.sale_conditions.settlement_type.get().value()) << '"'
       << ",prior_day_original_trade.sale_conditions.trade_through_exempt_reason=\"" << cta_output::trade_through_exempt_reason::to_string(msg.fields.prior_day_original_trade.sale_conditions.trade_through_exempt_reason.get().value()) << '"'
       << ",prior_day_original_trade.sale_conditions.extended_hours_or_sequence_type=\"" << cta_output::extended_hours_or_sequence_type::to_string(msg.fields.prior_day_original_trade.sale_conditions.extended_hours_or_sequence_type.get().value()) << '"'
       << ",prior_day_original_trade.sale_conditions.sro_trade_detail=\"" << cta_output::sro_trade_detail::to_string(msg.fields.prior_day_original_trade.sale_conditions.sro_trade_detail.get().value()) << '"'
       << ",prior_day_original_trade.trade_price=" << msg.fields.prior_day_original_trade.trade_price.get().value()
       << ",prior_day_original_trade.trade_volume=" << msg.fields.prior_day_original_trade.trade_volume.get().value()
       << ",prior_day_original_trade.sellers_sale_days=" << static_cast<unsigned>(msg.fields.prior_day_original_trade.sellers_sale_days.get().value())
       << ",prior_day_original_trade.stop_stock_indicator=\"" << cta_output::stop_stock_indicator::to_string(msg.fields.prior_day_original_trade.stop_stock_indicator.get().value()) << '"'
       << ",prior_day_original_trade.trade_through_exempt_indicator=\"" << cta_output::trade_through_exempt_indicator::to_string(msg.fields.prior_day_original_trade.trade_through_exempt_indicator.get().value()) << '"'
       << ",prior_day_original_trade.short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.prior_day_original_trade.short_sale_restriction_indicator.get().value()) << '"'
       << ",prior_day_original_trade.prior_day_trade_date_and_time.seconds=" << msg.fields.prior_day_original_trade.prior_day_trade_date_and_time.seconds.get().value()
       << ",prior_day_original_trade.prior_day_trade_date_and_time.nanoseconds=" << msg.fields.prior_day_original_trade.prior_day_trade_date_and_time.nanoseconds.get().value()
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
       << ",fractional_prior_day_corrected_trade.sale_conditions.settlement_type=\"" << cta_output::settlement_type::to_string(msg.fields.fractional_prior_day_corrected_trade.sale_conditions.settlement_type.get().value()) << '"'
       << ",fractional_prior_day_corrected_trade.sale_conditions.trade_through_exempt_reason=\"" << cta_output::trade_through_exempt_reason::to_string(msg.fields.fractional_prior_day_corrected_trade.sale_conditions.trade_through_exempt_reason.get().value()) << '"'
       << ",fractional_prior_day_corrected_trade.sale_conditions.extended_hours_or_sequence_type=\"" << cta_output::extended_hours_or_sequence_type::to_string(msg.fields.fractional_prior_day_corrected_trade.sale_conditions.extended_hours_or_sequence_type.get().value()) << '"'
       << ",fractional_prior_day_corrected_trade.sale_conditions.sro_trade_detail=\"" << cta_output::sro_trade_detail::to_string(msg.fields.fractional_prior_day_corrected_trade.sale_conditions.sro_trade_detail.get().value()) << '"'
       << ",fractional_prior_day_corrected_trade.trade_price=" << msg.fields.fractional_prior_day_corrected_trade.trade_price.get().value()
       << ",fractional_prior_day_corrected_trade.fractional_trade_volume=" << msg.fields.fractional_prior_day_corrected_trade.fractional_trade_volume.get().value()
       << ",fractional_prior_day_corrected_trade.sellers_sale_days=" << static_cast<unsigned>(msg.fields.fractional_prior_day_corrected_trade.sellers_sale_days.get().value())
       << ",fractional_prior_day_corrected_trade.stop_stock_indicator=\"" << cta_output::stop_stock_indicator::to_string(msg.fields.fractional_prior_day_corrected_trade.stop_stock_indicator.get().value()) << '"'
       << ",fractional_prior_day_corrected_trade.trade_through_exempt_indicator=\"" << cta_output::trade_through_exempt_indicator::to_string(msg.fields.fractional_prior_day_corrected_trade.trade_through_exempt_indicator.get().value()) << '"'
       << ",fractional_prior_day_corrected_trade.short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.fractional_prior_day_corrected_trade.short_sale_restriction_indicator.get().value()) << '"'
       << ",fractional_prior_day_corrected_trade.prior_day_trade_date_and_time.seconds=" << msg.fields.fractional_prior_day_corrected_trade.prior_day_trade_date_and_time.seconds.get().value()
       << ",fractional_prior_day_corrected_trade.prior_day_trade_date_and_time.nanoseconds=" << msg.fields.fractional_prior_day_corrected_trade.prior_day_trade_date_and_time.nanoseconds.get().value()
       << ",trade_reporting_facility_id=\"" << cta_output::trade_reporting_facility_id::to_string(msg.fields.trade_reporting_facility_id.get().value()) << '"'
       << ",fractional_prior_day_original_trade.sale_conditions.settlement_type=\"" << cta_output::settlement_type::to_string(msg.fields.fractional_prior_day_original_trade.sale_conditions.settlement_type.get().value()) << '"'
       << ",fractional_prior_day_original_trade.sale_conditions.trade_through_exempt_reason=\"" << cta_output::trade_through_exempt_reason::to_string(msg.fields.fractional_prior_day_original_trade.sale_conditions.trade_through_exempt_reason.get().value()) << '"'
       << ",fractional_prior_day_original_trade.sale_conditions.extended_hours_or_sequence_type=\"" << cta_output::extended_hours_or_sequence_type::to_string(msg.fields.fractional_prior_day_original_trade.sale_conditions.extended_hours_or_sequence_type.get().value()) << '"'
       << ",fractional_prior_day_original_trade.sale_conditions.sro_trade_detail=\"" << cta_output::sro_trade_detail::to_string(msg.fields.fractional_prior_day_original_trade.sale_conditions.sro_trade_detail.get().value()) << '"'
       << ",fractional_prior_day_original_trade.trade_price=" << msg.fields.fractional_prior_day_original_trade.trade_price.get().value()
       << ",fractional_prior_day_original_trade.fractional_trade_volume=" << msg.fields.fractional_prior_day_original_trade.fractional_trade_volume.get().value()
       << ",fractional_prior_day_original_trade.sellers_sale_days=" << static_cast<unsigned>(msg.fields.fractional_prior_day_original_trade.sellers_sale_days.get().value())
       << ",fractional_prior_day_original_trade.stop_stock_indicator=\"" << cta_output::stop_stock_indicator::to_string(msg.fields.fractional_prior_day_original_trade.stop_stock_indicator.get().value()) << '"'
       << ",fractional_prior_day_original_trade.trade_through_exempt_indicator=\"" << cta_output::trade_through_exempt_indicator::to_string(msg.fields.fractional_prior_day_original_trade.trade_through_exempt_indicator.get().value()) << '"'
       << ",fractional_prior_day_original_trade.short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.fractional_prior_day_original_trade.short_sale_restriction_indicator.get().value()) << '"'
       << ",fractional_prior_day_original_trade.prior_day_trade_date_and_time.seconds=" << msg.fields.fractional_prior_day_original_trade.prior_day_trade_date_and_time.seconds.get().value()
       << ",fractional_prior_day_original_trade.prior_day_trade_date_and_time.nanoseconds=" << msg.fields.fractional_prior_day_original_trade.prior_day_trade_date_and_time.nanoseconds.get().value()
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
       << ",sale_conditions.settlement_type=\"" << cta_output::settlement_type::to_string(msg.fields.sale_conditions.settlement_type.get().value()) << '"'
       << ",sale_conditions.trade_through_exempt_reason=\"" << cta_output::trade_through_exempt_reason::to_string(msg.fields.sale_conditions.trade_through_exempt_reason.get().value()) << '"'
       << ",sale_conditions.extended_hours_or_sequence_type=\"" << cta_output::extended_hours_or_sequence_type::to_string(msg.fields.sale_conditions.extended_hours_or_sequence_type.get().value()) << '"'
       << ",sale_conditions.sro_trade_detail=\"" << cta_output::sro_trade_detail::to_string(msg.fields.sale_conditions.sro_trade_detail.get().value()) << '"'
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

inline std::ostream& operator<<(std::ostream& os, const fractional_prior_day_trade_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",sale_conditions.settlement_type=\"" << cta_output::settlement_type::to_string(msg.fields.sale_conditions.settlement_type.get().value()) << '"'
       << ",sale_conditions.trade_through_exempt_reason=\"" << cta_output::trade_through_exempt_reason::to_string(msg.fields.sale_conditions.trade_through_exempt_reason.get().value()) << '"'
       << ",sale_conditions.extended_hours_or_sequence_type=\"" << cta_output::extended_hours_or_sequence_type::to_string(msg.fields.sale_conditions.extended_hours_or_sequence_type.get().value()) << '"'
       << ",sale_conditions.sro_trade_detail=\"" << cta_output::sro_trade_detail::to_string(msg.fields.sale_conditions.sro_trade_detail.get().value()) << '"'
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

inline std::ostream& operator<<(std::ostream& os, const prior_day_trade_cancel_error_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",sale_conditions.settlement_type=\"" << cta_output::settlement_type::to_string(msg.fields.sale_conditions.settlement_type.get().value()) << '"'
       << ",sale_conditions.trade_through_exempt_reason=\"" << cta_output::trade_through_exempt_reason::to_string(msg.fields.sale_conditions.trade_through_exempt_reason.get().value()) << '"'
       << ",sale_conditions.extended_hours_or_sequence_type=\"" << cta_output::extended_hours_or_sequence_type::to_string(msg.fields.sale_conditions.extended_hours_or_sequence_type.get().value()) << '"'
       << ",sale_conditions.sro_trade_detail=\"" << cta_output::sro_trade_detail::to_string(msg.fields.sale_conditions.sro_trade_detail.get().value()) << '"'
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

inline std::ostream& operator<<(std::ostream& os, const fractional_prior_day_trade_cancel_error_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",sale_conditions.settlement_type=\"" << cta_output::settlement_type::to_string(msg.fields.sale_conditions.settlement_type.get().value()) << '"'
       << ",sale_conditions.trade_through_exempt_reason=\"" << cta_output::trade_through_exempt_reason::to_string(msg.fields.sale_conditions.trade_through_exempt_reason.get().value()) << '"'
       << ",sale_conditions.extended_hours_or_sequence_type=\"" << cta_output::extended_hours_or_sequence_type::to_string(msg.fields.sale_conditions.extended_hours_or_sequence_type.get().value()) << '"'
       << ",sale_conditions.sro_trade_detail=\"" << cta_output::sro_trade_detail::to_string(msg.fields.sale_conditions.sro_trade_detail.get().value()) << '"'
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
       << ",last_participant_id=\"" << cta_output::last_participant_id::to_string(msg.fields.last_participant_id.get().value()) << '"'
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
       << ",last_participant_id=\"" << cta_output::last_participant_id::to_string(msg.fields.last_participant_id.get().value()) << '"'
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
       << ",initiating_participant_id=\"" << cta_output::initiating_participant_id::to_string(msg.fields.initiating_participant_id.get().value()) << '"'
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
       << ",initiating_participant_id=\"" << cta_output::initiating_participant_id::to_string(msg.fields.initiating_participant_id.get().value()) << '"'
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
       << ",future_use=\"" << msg.fields.future_use.get_trimmed().value() << '"'
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
       << ",corrected_trade.sale_conditions.settlement_type=\"" << cta_output::settlement_type::to_string(msg.fields.corrected_trade.sale_conditions.settlement_type.get().value()) << '"'
       << ",corrected_trade.sale_conditions.trade_through_exempt_reason=\"" << cta_output::trade_through_exempt_reason::to_string(msg.fields.corrected_trade.sale_conditions.trade_through_exempt_reason.get().value()) << '"'
       << ",corrected_trade.sale_conditions.extended_hours_or_sequence_type=\"" << cta_output::extended_hours_or_sequence_type::to_string(msg.fields.corrected_trade.sale_conditions.extended_hours_or_sequence_type.get().value()) << '"'
       << ",corrected_trade.sale_conditions.sro_trade_detail=\"" << cta_output::sro_trade_detail::to_string(msg.fields.corrected_trade.sale_conditions.sro_trade_detail.get().value()) << '"'
       << ",corrected_trade.trade_price=" << msg.fields.corrected_trade.trade_price.get().value()
       << ",corrected_trade.trade_volume=" << msg.fields.corrected_trade.trade_volume.get().value()
       << ",corrected_trade.sellers_sale_days=" << static_cast<unsigned>(msg.fields.corrected_trade.sellers_sale_days.get().value())
       << ",corrected_trade.stop_stock_indicator=\"" << cta_output::stop_stock_indicator::to_string(msg.fields.corrected_trade.stop_stock_indicator.get().value()) << '"'
       << ",corrected_trade.trade_through_exempt_indicator=\"" << cta_output::trade_through_exempt_indicator::to_string(msg.fields.corrected_trade.trade_through_exempt_indicator.get().value()) << '"'
       << ",corrected_trade.short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.corrected_trade.short_sale_restriction_indicator.get().value()) << '"'
       << ",trade_reporting_facility_id=\"" << cta_output::trade_reporting_facility_id::to_string(msg.fields.trade_reporting_facility_id.get().value()) << '"'
       << ",timestamp_2=" << (msg.fields.timestamp_2.get().has_value() ? std::to_string(msg.fields.timestamp_2.get().value()) : std::string_view("null"))
       << ",original_participant_reference_number=" << msg.fields.original_participant_reference_number.get().value()
       << ",original_trade.sale_conditions.settlement_type=\"" << cta_output::settlement_type::to_string(msg.fields.original_trade.sale_conditions.settlement_type.get().value()) << '"'
       << ",original_trade.sale_conditions.trade_through_exempt_reason=\"" << cta_output::trade_through_exempt_reason::to_string(msg.fields.original_trade.sale_conditions.trade_through_exempt_reason.get().value()) << '"'
       << ",original_trade.sale_conditions.extended_hours_or_sequence_type=\"" << cta_output::extended_hours_or_sequence_type::to_string(msg.fields.original_trade.sale_conditions.extended_hours_or_sequence_type.get().value()) << '"'
       << ",original_trade.sale_conditions.sro_trade_detail=\"" << cta_output::sro_trade_detail::to_string(msg.fields.original_trade.sale_conditions.sro_trade_detail.get().value()) << '"'
       << ",original_trade.trade_price=" << msg.fields.original_trade.trade_price.get().value()
       << ",original_trade.trade_volume=" << msg.fields.original_trade.trade_volume.get().value()
       << ",original_trade.sellers_sale_days=" << static_cast<unsigned>(msg.fields.original_trade.sellers_sale_days.get().value())
       << ",original_trade.stop_stock_indicator=\"" << cta_output::stop_stock_indicator::to_string(msg.fields.original_trade.stop_stock_indicator.get().value()) << '"'
       << ",original_trade.trade_through_exempt_indicator=\"" << cta_output::trade_through_exempt_indicator::to_string(msg.fields.original_trade.trade_through_exempt_indicator.get().value()) << '"'
       << ",original_trade.short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.original_trade.short_sale_restriction_indicator.get().value()) << '"'
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",financial_status_indicator=\"" << cta_output::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       << ",consolidated_data.previous_close_price_date=" << msg.fields.consolidated_data.previous_close_price_date.get().value()
       << ",consolidated_data.last_participant_id=\"" << cta_output::last_participant_id::to_string(msg.fields.consolidated_data.last_participant_id.get().value()) << '"'
       << ",consolidated_data.last_price=" << msg.fields.consolidated_data.last_price.get().value()
       << ",consolidated_data.high_price=" << msg.fields.consolidated_data.high_price.get().value()
       << ",consolidated_data.low_price=" << msg.fields.consolidated_data.low_price.get().value()
       << ",consolidated_data.total_volume_short=" << msg.fields.consolidated_data.total_volume_short.get().value()
       << ",consolidated_data.tick=\"" << cta_output::tick::to_string(msg.fields.consolidated_data.tick.get().value()) << '"'
       << ",participant_data.previous_close_price_date=" << msg.fields.participant_data.previous_close_price_date.get().value()
       << ",participant_data.last_price=" << msg.fields.participant_data.last_price.get().value()
       << ",participant_data.high_price=" << msg.fields.participant_data.high_price.get().value()
       << ",participant_data.low_price=" << msg.fields.participant_data.low_price.get().value()
       << ",participant_data.open_price=" << msg.fields.participant_data.open_price.get().value()
       << ",participant_data.total_volume_short=" << msg.fields.participant_data.total_volume_short.get().value()
       << ",participant_data.tick=\"" << cta_output::tick::to_string(msg.fields.participant_data.tick.get().value()) << '"'
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
       << ",fractional_corrected_trade.sale_conditions.settlement_type=\"" << cta_output::settlement_type::to_string(msg.fields.fractional_corrected_trade.sale_conditions.settlement_type.get().value()) << '"'
       << ",fractional_corrected_trade.sale_conditions.trade_through_exempt_reason=\"" << cta_output::trade_through_exempt_reason::to_string(msg.fields.fractional_corrected_trade.sale_conditions.trade_through_exempt_reason.get().value()) << '"'
       << ",fractional_corrected_trade.sale_conditions.extended_hours_or_sequence_type=\"" << cta_output::extended_hours_or_sequence_type::to_string(msg.fields.fractional_corrected_trade.sale_conditions.extended_hours_or_sequence_type.get().value()) << '"'
       << ",fractional_corrected_trade.sale_conditions.sro_trade_detail=\"" << cta_output::sro_trade_detail::to_string(msg.fields.fractional_corrected_trade.sale_conditions.sro_trade_detail.get().value()) << '"'
       << ",fractional_corrected_trade.trade_price=" << msg.fields.fractional_corrected_trade.trade_price.get().value()
       << ",fractional_corrected_trade.fractional_trade_volume=" << msg.fields.fractional_corrected_trade.fractional_trade_volume.get().value()
       << ",fractional_corrected_trade.sellers_sale_days=" << static_cast<unsigned>(msg.fields.fractional_corrected_trade.sellers_sale_days.get().value())
       << ",fractional_corrected_trade.stop_stock_indicator=\"" << cta_output::stop_stock_indicator::to_string(msg.fields.fractional_corrected_trade.stop_stock_indicator.get().value()) << '"'
       << ",fractional_corrected_trade.trade_through_exempt_indicator=\"" << cta_output::trade_through_exempt_indicator::to_string(msg.fields.fractional_corrected_trade.trade_through_exempt_indicator.get().value()) << '"'
       << ",fractional_corrected_trade.short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.fractional_corrected_trade.short_sale_restriction_indicator.get().value()) << '"'
       << ",trade_reporting_facility_id=\"" << cta_output::trade_reporting_facility_id::to_string(msg.fields.trade_reporting_facility_id.get().value()) << '"'
       << ",timestamp_2=" << (msg.fields.timestamp_2.get().has_value() ? std::to_string(msg.fields.timestamp_2.get().value()) : std::string_view("null"))
       << ",original_participant_reference_number=" << msg.fields.original_participant_reference_number.get().value()
       << ",fractional_original_trade.sale_conditions.settlement_type=\"" << cta_output::settlement_type::to_string(msg.fields.fractional_original_trade.sale_conditions.settlement_type.get().value()) << '"'
       << ",fractional_original_trade.sale_conditions.trade_through_exempt_reason=\"" << cta_output::trade_through_exempt_reason::to_string(msg.fields.fractional_original_trade.sale_conditions.trade_through_exempt_reason.get().value()) << '"'
       << ",fractional_original_trade.sale_conditions.extended_hours_or_sequence_type=\"" << cta_output::extended_hours_or_sequence_type::to_string(msg.fields.fractional_original_trade.sale_conditions.extended_hours_or_sequence_type.get().value()) << '"'
       << ",fractional_original_trade.sale_conditions.sro_trade_detail=\"" << cta_output::sro_trade_detail::to_string(msg.fields.fractional_original_trade.sale_conditions.sro_trade_detail.get().value()) << '"'
       << ",fractional_original_trade.trade_price=" << msg.fields.fractional_original_trade.trade_price.get().value()
       << ",fractional_original_trade.fractional_trade_volume=" << msg.fields.fractional_original_trade.fractional_trade_volume.get().value()
       << ",fractional_original_trade.sellers_sale_days=" << static_cast<unsigned>(msg.fields.fractional_original_trade.sellers_sale_days.get().value())
       << ",fractional_original_trade.stop_stock_indicator=\"" << cta_output::stop_stock_indicator::to_string(msg.fields.fractional_original_trade.stop_stock_indicator.get().value()) << '"'
       << ",fractional_original_trade.trade_through_exempt_indicator=\"" << cta_output::trade_through_exempt_indicator::to_string(msg.fields.fractional_original_trade.trade_through_exempt_indicator.get().value()) << '"'
       << ",fractional_original_trade.short_sale_restriction_indicator=\"" << cta_output::short_sale_restriction_indicator::to_string(msg.fields.fractional_original_trade.short_sale_restriction_indicator.get().value()) << '"'
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",financial_status_indicator=\"" << cta_output::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       << ",fractional_consolidated_data.previous_close_price_date=" << msg.fields.fractional_consolidated_data.previous_close_price_date.get().value()
       << ",fractional_consolidated_data.last_participant_id=\"" << cta_output::last_participant_id::to_string(msg.fields.fractional_consolidated_data.last_participant_id.get().value()) << '"'
       << ",fractional_consolidated_data.last_price=" << msg.fields.fractional_consolidated_data.last_price.get().value()
       << ",fractional_consolidated_data.high_price=" << msg.fields.fractional_consolidated_data.high_price.get().value()
       << ",fractional_consolidated_data.low_price=" << msg.fields.fractional_consolidated_data.low_price.get().value()
       << ",fractional_consolidated_data.fractional_total_volume=" << msg.fields.fractional_consolidated_data.fractional_total_volume.get().value()
       << ",fractional_consolidated_data.tick=\"" << cta_output::tick::to_string(msg.fields.fractional_consolidated_data.tick.get().value()) << '"'
       << ",fractional_participant_data.previous_close_price_date=" << msg.fields.fractional_participant_data.previous_close_price_date.get().value()
       << ",fractional_participant_data.last_price=" << msg.fields.fractional_participant_data.last_price.get().value()
       << ",fractional_participant_data.high_price=" << msg.fields.fractional_participant_data.high_price.get().value()
       << ",fractional_participant_data.low_price=" << msg.fields.fractional_participant_data.low_price.get().value()
       << ",fractional_participant_data.open_price=" << msg.fields.fractional_participant_data.open_price.get().value()
       << ",fractional_participant_data.fractional_total_volume=" << msg.fields.fractional_participant_data.fractional_total_volume.get().value()
       << ",fractional_participant_data.tick=\"" << cta_output::tick::to_string(msg.fields.fractional_participant_data.tick.get().value()) << '"'
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
       << ",sale_conditions.settlement_type=\"" << cta_output::settlement_type::to_string(msg.fields.sale_conditions.settlement_type.get().value()) << '"'
       << ",sale_conditions.trade_through_exempt_reason=\"" << cta_output::trade_through_exempt_reason::to_string(msg.fields.sale_conditions.trade_through_exempt_reason.get().value()) << '"'
       << ",sale_conditions.extended_hours_or_sequence_type=\"" << cta_output::extended_hours_or_sequence_type::to_string(msg.fields.sale_conditions.extended_hours_or_sequence_type.get().value()) << '"'
       << ",sale_conditions.sro_trade_detail=\"" << cta_output::sro_trade_detail::to_string(msg.fields.sale_conditions.sro_trade_detail.get().value()) << '"'
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

inline std::ostream& operator<<(std::ostream& os, const fractional_long_trade_message& msg) {
    os << "participant_id=\"" << cta_output::participant_id::to_string(msg.fields.participant_id.get().value()) << '"'
       << ",timestamp_1.seconds=" << msg.fields.timestamp_1.seconds.get().value()
       << ",timestamp_1.nanoseconds=" << msg.fields.timestamp_1.nanoseconds.get().value()
       << ",message_id=" << static_cast<unsigned>(msg.fields.message_id.get().value())
       << ",transaction_id=" << msg.fields.transaction_id.get().value()
       << ",participant_reference_number=" << msg.fields.participant_reference_number.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",instrument_type=\"" << cta_output::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",sale_conditions.settlement_type=\"" << cta_output::settlement_type::to_string(msg.fields.sale_conditions.settlement_type.get().value()) << '"'
       << ",sale_conditions.trade_through_exempt_reason=\"" << cta_output::trade_through_exempt_reason::to_string(msg.fields.sale_conditions.trade_through_exempt_reason.get().value()) << '"'
       << ",sale_conditions.extended_hours_or_sequence_type=\"" << cta_output::extended_hours_or_sequence_type::to_string(msg.fields.sale_conditions.extended_hours_or_sequence_type.get().value()) << '"'
       << ",sale_conditions.sro_trade_detail=\"" << cta_output::sro_trade_detail::to_string(msg.fields.sale_conditions.sro_trade_detail.get().value()) << '"'
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
       << ",limit_up_limit_down_indicator=\"" << cta_output::limit_up_limit_down_indicator::to_string(msg.fields.limit_up_limit_down_indicator.get().value()) << '"'
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
       << ",security_symbol_short=\"" << msg.fields.security_symbol_short.get_trimmed().value() << '"'
       << ",sale_condition=\"" << cta_output::sale_condition::to_string(msg.fields.sale_condition.get().value()) << '"'
       << ",sale_condition_category=\"" << cta_output::sale_condition_category::to_string(msg.fields.sale_condition_category.get().value()) << '"'
       << ",trade_price_short=" << msg.fields.trade_price_short.get().value()
       << ",trade_volume_short=" << msg.fields.trade_volume_short.get().value()
       << ",primary_listing_market_participant_id=\"" << cta_output::primary_listing_market_participant_id::to_string(msg.fields.primary_listing_market_participant_id.get().value()) << '"'
       << ",consolidated_high_low_last_indicator=\"" << cta_output::consolidated_high_low_last_indicator::to_string(msg.fields.consolidated_high_low_last_indicator.get().value()) << '"'
       << ",participant_open_high_low_last_indicator=\"" << cta_output::participant_open_high_low_last_indicator::to_string(msg.fields.participant_open_high_low_last_indicator.get().value()) << '"'
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
       << ",security_symbol_short=\"" << msg.fields.security_symbol_short.get_trimmed().value() << '"'
       << ",sale_condition=\"" << cta_output::sale_condition::to_string(msg.fields.sale_condition.get().value()) << '"'
       << ",sale_condition_category=\"" << cta_output::sale_condition_category::to_string(msg.fields.sale_condition_category.get().value()) << '"'
       << ",trade_price_short=" << msg.fields.trade_price_short.get().value()
       << ",fractional_trade_volume_short=" << msg.fields.fractional_trade_volume_short.get().value()
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
       << ",sale_conditions.settlement_type=\"" << cta_output::settlement_type::to_string(msg.fields.sale_conditions.settlement_type.get().value()) << '"'
       << ",sale_conditions.trade_through_exempt_reason=\"" << cta_output::trade_through_exempt_reason::to_string(msg.fields.sale_conditions.trade_through_exempt_reason.get().value()) << '"'
       << ",sale_conditions.extended_hours_or_sequence_type=\"" << cta_output::extended_hours_or_sequence_type::to_string(msg.fields.sale_conditions.extended_hours_or_sequence_type.get().value()) << '"'
       << ",sale_conditions.sro_trade_detail=\"" << cta_output::sro_trade_detail::to_string(msg.fields.sale_conditions.sro_trade_detail.get().value()) << '"'
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
       << ",consolidated_data.previous_close_price_date=" << msg.fields.consolidated_data.previous_close_price_date.get().value()
       << ",consolidated_data.last_participant_id=\"" << cta_output::last_participant_id::to_string(msg.fields.consolidated_data.last_participant_id.get().value()) << '"'
       << ",consolidated_data.last_price=" << msg.fields.consolidated_data.last_price.get().value()
       << ",consolidated_data.high_price=" << msg.fields.consolidated_data.high_price.get().value()
       << ",consolidated_data.low_price=" << msg.fields.consolidated_data.low_price.get().value()
       << ",consolidated_data.total_volume_short=" << msg.fields.consolidated_data.total_volume_short.get().value()
       << ",consolidated_data.tick=\"" << cta_output::tick::to_string(msg.fields.consolidated_data.tick.get().value()) << '"'
       << ",participant_data.previous_close_price_date=" << msg.fields.participant_data.previous_close_price_date.get().value()
       << ",participant_data.last_price=" << msg.fields.participant_data.last_price.get().value()
       << ",participant_data.high_price=" << msg.fields.participant_data.high_price.get().value()
       << ",participant_data.low_price=" << msg.fields.participant_data.low_price.get().value()
       << ",participant_data.open_price=" << msg.fields.participant_data.open_price.get().value()
       << ",participant_data.total_volume_short=" << msg.fields.participant_data.total_volume_short.get().value()
       << ",participant_data.tick=\"" << cta_output::tick::to_string(msg.fields.participant_data.tick.get().value()) << '"'
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
       << ",sale_conditions.settlement_type=\"" << cta_output::settlement_type::to_string(msg.fields.sale_conditions.settlement_type.get().value()) << '"'
       << ",sale_conditions.trade_through_exempt_reason=\"" << cta_output::trade_through_exempt_reason::to_string(msg.fields.sale_conditions.trade_through_exempt_reason.get().value()) << '"'
       << ",sale_conditions.extended_hours_or_sequence_type=\"" << cta_output::extended_hours_or_sequence_type::to_string(msg.fields.sale_conditions.extended_hours_or_sequence_type.get().value()) << '"'
       << ",sale_conditions.sro_trade_detail=\"" << cta_output::sro_trade_detail::to_string(msg.fields.sale_conditions.sro_trade_detail.get().value()) << '"'
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
       << ",fractional_consolidated_data.previous_close_price_date=" << msg.fields.fractional_consolidated_data.previous_close_price_date.get().value()
       << ",fractional_consolidated_data.last_participant_id=\"" << cta_output::last_participant_id::to_string(msg.fields.fractional_consolidated_data.last_participant_id.get().value()) << '"'
       << ",fractional_consolidated_data.last_price=" << msg.fields.fractional_consolidated_data.last_price.get().value()
       << ",fractional_consolidated_data.high_price=" << msg.fields.fractional_consolidated_data.high_price.get().value()
       << ",fractional_consolidated_data.low_price=" << msg.fields.fractional_consolidated_data.low_price.get().value()
       << ",fractional_consolidated_data.fractional_total_volume=" << msg.fields.fractional_consolidated_data.fractional_total_volume.get().value()
       << ",fractional_consolidated_data.tick=\"" << cta_output::tick::to_string(msg.fields.fractional_consolidated_data.tick.get().value()) << '"'
       << ",fractional_participant_data.previous_close_price_date=" << msg.fields.fractional_participant_data.previous_close_price_date.get().value()
       << ",fractional_participant_data.last_price=" << msg.fields.fractional_participant_data.last_price.get().value()
       << ",fractional_participant_data.high_price=" << msg.fields.fractional_participant_data.high_price.get().value()
       << ",fractional_participant_data.low_price=" << msg.fields.fractional_participant_data.low_price.get().value()
       << ",fractional_participant_data.open_price=" << msg.fields.fractional_participant_data.open_price.get().value()
       << ",fractional_participant_data.fractional_total_volume=" << msg.fields.fractional_participant_data.fractional_total_volume.get().value()
       << ",fractional_participant_data.tick=\"" << cta_output::tick::to_string(msg.fields.fractional_participant_data.tick.get().value()) << '"'
       ;
    return os;
}

}
