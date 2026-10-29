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
#include "../structs/SaleConditions.hpp"
#include "../types/TradePrice.hpp"
#include "../types/FractionalTradeVolume.hpp"
#include "../types/SellersSaleDays.hpp"
#include "../types/StopStockIndicator.hpp"
#include "../types/TradeThroughExemptIndicator.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/TradeReportingFacilityId.hpp"
#include "../structs/PriorDayTradeDateAndTime.hpp"
#include "../types/CancelErrorAction.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/PriorDayMessageType.hpp"

namespace siac::cts::output::cta::v2_10 {

namespace cta_output = ::siac::cts::output::cta::v2_10;

#pragma pack(push, 1)

// Fractional Prior Day Trade Cancel Error Message
struct fractional_prior_day_trade_cancel_error_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::timestamp_1 timestamp_1;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::security_symbol security_symbol;
        cta_output::instrument_type instrument_type;
        cta_output::sale_conditions sale_conditions;
        cta_output::trade_price trade_price;
        cta_output::fractional_trade_volume fractional_trade_volume;
        cta_output::sellers_sale_days sellers_sale_days;
        cta_output::stop_stock_indicator stop_stock_indicator;
        cta_output::trade_through_exempt_indicator trade_through_exempt_indicator;
        cta_output::short_sale_restriction_indicator short_sale_restriction_indicator;
        cta_output::trade_reporting_facility_id trade_reporting_facility_id;
        cta_output::prior_day_trade_date_and_time prior_day_trade_date_and_time;
        cta_output::cancel_error_action cancel_error_action;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::prior_day;
    cta_output::prior_day_message_type prior_day_message_type = cta_output::prior_day_message_type::enum_type::fractional_prior_day_trade_cancel_error_message;

    fields_type fields;

    // parse method
    static fractional_prior_day_trade_cancel_error_message* parse(std::byte* buffer) {
        return reinterpret_cast<fractional_prior_day_trade_cancel_error_message*>(buffer);
    }

    // parse method const
    static const fractional_prior_day_trade_cancel_error_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const fractional_prior_day_trade_cancel_error_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(fractional_prior_day_trade_cancel_error_message::fields_type, participant_id) == 0, "unexpected offset of fractional_prior_day_trade_cancel_error_message::fields_type::participant_id");
static_assert(offsetof(fractional_prior_day_trade_cancel_error_message::fields_type, timestamp_1) == 1, "unexpected offset of fractional_prior_day_trade_cancel_error_message::fields_type::timestamp_1");
static_assert(offsetof(fractional_prior_day_trade_cancel_error_message::fields_type, message_id) == 9, "unexpected offset of fractional_prior_day_trade_cancel_error_message::fields_type::message_id");
static_assert(offsetof(fractional_prior_day_trade_cancel_error_message::fields_type, transaction_id) == 10, "unexpected offset of fractional_prior_day_trade_cancel_error_message::fields_type::transaction_id");
static_assert(offsetof(fractional_prior_day_trade_cancel_error_message::fields_type, participant_reference_number) == 14, "unexpected offset of fractional_prior_day_trade_cancel_error_message::fields_type::participant_reference_number");
static_assert(offsetof(fractional_prior_day_trade_cancel_error_message::fields_type, security_symbol) == 22, "unexpected offset of fractional_prior_day_trade_cancel_error_message::fields_type::security_symbol");
static_assert(offsetof(fractional_prior_day_trade_cancel_error_message::fields_type, instrument_type) == 33, "unexpected offset of fractional_prior_day_trade_cancel_error_message::fields_type::instrument_type");
static_assert(offsetof(fractional_prior_day_trade_cancel_error_message::fields_type, sale_conditions) == 34, "unexpected offset of fractional_prior_day_trade_cancel_error_message::fields_type::sale_conditions");
static_assert(offsetof(fractional_prior_day_trade_cancel_error_message::fields_type, trade_price) == 38, "unexpected offset of fractional_prior_day_trade_cancel_error_message::fields_type::trade_price");
static_assert(offsetof(fractional_prior_day_trade_cancel_error_message::fields_type, fractional_trade_volume) == 46, "unexpected offset of fractional_prior_day_trade_cancel_error_message::fields_type::fractional_trade_volume");
static_assert(offsetof(fractional_prior_day_trade_cancel_error_message::fields_type, sellers_sale_days) == 54, "unexpected offset of fractional_prior_day_trade_cancel_error_message::fields_type::sellers_sale_days");
static_assert(offsetof(fractional_prior_day_trade_cancel_error_message::fields_type, stop_stock_indicator) == 55, "unexpected offset of fractional_prior_day_trade_cancel_error_message::fields_type::stop_stock_indicator");
static_assert(offsetof(fractional_prior_day_trade_cancel_error_message::fields_type, trade_through_exempt_indicator) == 56, "unexpected offset of fractional_prior_day_trade_cancel_error_message::fields_type::trade_through_exempt_indicator");
static_assert(offsetof(fractional_prior_day_trade_cancel_error_message::fields_type, short_sale_restriction_indicator) == 57, "unexpected offset of fractional_prior_day_trade_cancel_error_message::fields_type::short_sale_restriction_indicator");
static_assert(offsetof(fractional_prior_day_trade_cancel_error_message::fields_type, trade_reporting_facility_id) == 58, "unexpected offset of fractional_prior_day_trade_cancel_error_message::fields_type::trade_reporting_facility_id");
static_assert(offsetof(fractional_prior_day_trade_cancel_error_message::fields_type, prior_day_trade_date_and_time) == 59, "unexpected offset of fractional_prior_day_trade_cancel_error_message::fields_type::prior_day_trade_date_and_time");
static_assert(offsetof(fractional_prior_day_trade_cancel_error_message::fields_type, cancel_error_action) == 67, "unexpected offset of fractional_prior_day_trade_cancel_error_message::fields_type::cancel_error_action");
static_assert(sizeof(fractional_prior_day_trade_cancel_error_message::fields_type) == 68, "unexpected sizeof fractional_prior_day_trade_cancel_error_message::fields_type");
static_assert(sizeof(fractional_prior_day_trade_cancel_error_message) == sizeof(cta_output::block_header) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::prior_day_message_type) + 68, "unexpected sizeof fractional_prior_day_trade_cancel_error_message");

#pragma pack(pop)
}
