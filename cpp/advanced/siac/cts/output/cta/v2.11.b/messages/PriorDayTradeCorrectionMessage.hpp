#pragma once

#include <cstddef>
#include "../structs/BlockHeader.hpp"
#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/InstrumentType.hpp"
#include "../types/CorrectedSaleCondition.hpp"
#include "../types/CorrectedTradePrice.hpp"
#include "../types/CorrectedTradeVolume.hpp"
#include "../types/CorrectedSellersSaleDays.hpp"
#include "../types/CorrectedStopStockIndicator.hpp"
#include "../types/CorrectedTradeThroughExemptIndicator.hpp"
#include "../types/CorrectedShortSaleRestrictionIndicator.hpp"
#include "../structs/CorrectedPriorDayTradeDateAndTime.hpp"
#include "../types/TradeReportingFacilityId.hpp"
#include "../types/OriginalSaleCondition.hpp"
#include "../types/OriginalTradePrice.hpp"
#include "../types/OriginalTradeVolume.hpp"
#include "../types/OriginalSellersSaleDays.hpp"
#include "../types/OriginalStopStockIndicator.hpp"
#include "../types/OriginalTradeThroughExemptIndicator.hpp"
#include "../types/OriginalShortSaleRestrictionIndicator.hpp"
#include "../structs/OriginalPriorDayTradeDateAndTime.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/PriorDayMessageType.hpp"

namespace siac::cts::output::cta::v2_11_b {

namespace cta_output = ::siac::cts::output::cta::v2_11_b;

#pragma pack(push, 1)

// Prior Day Trade Correction Message
struct prior_day_trade_correction_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::timestamp_1 timestamp_1;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::security_symbol security_symbol;
        cta_output::instrument_type instrument_type;
        cta_output::corrected_sale_condition corrected_sale_condition;
        cta_output::corrected_trade_price corrected_trade_price;
        cta_output::corrected_trade_volume corrected_trade_volume;
        cta_output::corrected_sellers_sale_days corrected_sellers_sale_days;
        cta_output::corrected_stop_stock_indicator corrected_stop_stock_indicator;
        cta_output::corrected_trade_through_exempt_indicator corrected_trade_through_exempt_indicator;
        cta_output::corrected_short_sale_restriction_indicator corrected_short_sale_restriction_indicator;
        cta_output::corrected_prior_day_trade_date_and_time corrected_prior_day_trade_date_and_time;
        cta_output::trade_reporting_facility_id trade_reporting_facility_id;
        cta_output::original_sale_condition original_sale_condition;
        cta_output::original_trade_price original_trade_price;
        cta_output::original_trade_volume original_trade_volume;
        cta_output::original_sellers_sale_days original_sellers_sale_days;
        cta_output::original_stop_stock_indicator original_stop_stock_indicator;
        cta_output::original_trade_through_exempt_indicator original_trade_through_exempt_indicator;
        cta_output::original_short_sale_restriction_indicator original_short_sale_restriction_indicator;
        cta_output::original_prior_day_trade_date_and_time original_prior_day_trade_date_and_time;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::prior_day;
    cta_output::prior_day_message_type prior_day_message_type = cta_output::prior_day_message_type::enum_type::prior_day_trade_correction;

    fields_type fields;

    // parse method
    static prior_day_trade_correction_message* parse(std::byte* buffer) {
        return reinterpret_cast<prior_day_trade_correction_message*>(buffer);
    }

    // parse method const
    static const prior_day_trade_correction_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const prior_day_trade_correction_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(prior_day_trade_correction_message::fields_type, participant_id) == 0, "unexpected offset of prior_day_trade_correction_message::fields_type::participant_id");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, timestamp_1) == 1, "unexpected offset of prior_day_trade_correction_message::fields_type::timestamp_1");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, message_id) == 9, "unexpected offset of prior_day_trade_correction_message::fields_type::message_id");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, transaction_id) == 10, "unexpected offset of prior_day_trade_correction_message::fields_type::transaction_id");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, participant_reference_number) == 14, "unexpected offset of prior_day_trade_correction_message::fields_type::participant_reference_number");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, security_symbol) == 22, "unexpected offset of prior_day_trade_correction_message::fields_type::security_symbol");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, instrument_type) == 33, "unexpected offset of prior_day_trade_correction_message::fields_type::instrument_type");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, corrected_sale_condition) == 34, "unexpected offset of prior_day_trade_correction_message::fields_type::corrected_sale_condition");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, corrected_trade_price) == 38, "unexpected offset of prior_day_trade_correction_message::fields_type::corrected_trade_price");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, corrected_trade_volume) == 46, "unexpected offset of prior_day_trade_correction_message::fields_type::corrected_trade_volume");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, corrected_sellers_sale_days) == 50, "unexpected offset of prior_day_trade_correction_message::fields_type::corrected_sellers_sale_days");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, corrected_stop_stock_indicator) == 51, "unexpected offset of prior_day_trade_correction_message::fields_type::corrected_stop_stock_indicator");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, corrected_trade_through_exempt_indicator) == 52, "unexpected offset of prior_day_trade_correction_message::fields_type::corrected_trade_through_exempt_indicator");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, corrected_short_sale_restriction_indicator) == 53, "unexpected offset of prior_day_trade_correction_message::fields_type::corrected_short_sale_restriction_indicator");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, corrected_prior_day_trade_date_and_time) == 54, "unexpected offset of prior_day_trade_correction_message::fields_type::corrected_prior_day_trade_date_and_time");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, trade_reporting_facility_id) == 62, "unexpected offset of prior_day_trade_correction_message::fields_type::trade_reporting_facility_id");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, original_sale_condition) == 63, "unexpected offset of prior_day_trade_correction_message::fields_type::original_sale_condition");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, original_trade_price) == 67, "unexpected offset of prior_day_trade_correction_message::fields_type::original_trade_price");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, original_trade_volume) == 75, "unexpected offset of prior_day_trade_correction_message::fields_type::original_trade_volume");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, original_sellers_sale_days) == 79, "unexpected offset of prior_day_trade_correction_message::fields_type::original_sellers_sale_days");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, original_stop_stock_indicator) == 80, "unexpected offset of prior_day_trade_correction_message::fields_type::original_stop_stock_indicator");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, original_trade_through_exempt_indicator) == 81, "unexpected offset of prior_day_trade_correction_message::fields_type::original_trade_through_exempt_indicator");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, original_short_sale_restriction_indicator) == 82, "unexpected offset of prior_day_trade_correction_message::fields_type::original_short_sale_restriction_indicator");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, original_prior_day_trade_date_and_time) == 83, "unexpected offset of prior_day_trade_correction_message::fields_type::original_prior_day_trade_date_and_time");
static_assert(sizeof(prior_day_trade_correction_message::fields_type) == 91, "unexpected sizeof prior_day_trade_correction_message::fields_type");
static_assert(sizeof(prior_day_trade_correction_message) == sizeof(cta_output::block_header) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::prior_day_message_type) + 91, "unexpected sizeof prior_day_trade_correction_message");

#pragma pack(pop)
}
