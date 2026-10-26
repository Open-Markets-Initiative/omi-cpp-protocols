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
#include "../structs/SaleCondition4.hpp"
#include "../types/TradePrice.hpp"
#include "../types/TradeVolume.hpp"
#include "../types/SellersSaleDays.hpp"
#include "../types/StopStockIndicator.hpp"
#include "../types/TradeThroughExemptIndicator.hpp"
#include "../types/TradeReportingFacilityId.hpp"
#include "../types/OriginalParticipantReferenceNumber.hpp"
#include "../types/Timestamp2Optional.hpp"
#include "../types/CancelErrorAction.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/ConsolidatedPreviousClosePriceDate.hpp"
#include "../types/ConsolidatedLastParticipantId.hpp"
#include "../types/ConsolidatedLastPrice.hpp"
#include "../types/ConsolidatedHighPrice.hpp"
#include "../types/ConsolidatedLowPrice.hpp"
#include "../types/ConsolidatedTotalVolume.hpp"
#include "../types/ConsolidatedTick.hpp"
#include "../types/ParticipantPreviousClosePriceDate.hpp"
#include "../types/ParticipantLastPrice.hpp"
#include "../types/ParticipantHighPrice.hpp"
#include "../types/ParticipantLowPrice.hpp"
#include "../types/ParticipantOpenPrice.hpp"
#include "../types/ParticipantTotalVolume.hpp"
#include "../types/ParticipantTick.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/TradeMessageType.hpp"

namespace siac::cts::output::cta::v2_11_b {

namespace cta_output = ::siac::cts::output::cta::v2_11_b;

#pragma pack(push, 1)

// Trade Cancel Error Message
struct trade_cancel_error_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::timestamp_1 timestamp_1;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::security_symbol security_symbol;
        cta_output::instrument_type instrument_type;
        cta_output::sale_condition_4 sale_condition_4;
        cta_output::trade_price trade_price;
        cta_output::trade_volume trade_volume;
        cta_output::sellers_sale_days sellers_sale_days;
        cta_output::stop_stock_indicator stop_stock_indicator;
        cta_output::trade_through_exempt_indicator trade_through_exempt_indicator;
        cta_output::trade_reporting_facility_id trade_reporting_facility_id;
        cta_output::original_participant_reference_number original_participant_reference_number;
        cta_output::timestamp_2_optional timestamp_2;
        cta_output::cancel_error_action cancel_error_action;
        cta_output::short_sale_restriction_indicator short_sale_restriction_indicator;
        cta_output::primary_listing_market_participant_id primary_listing_market_participant_id;
        cta_output::financial_status_indicator financial_status_indicator;
        cta_output::consolidated_previous_close_price_date consolidated_previous_close_price_date;
        cta_output::consolidated_last_participant_id consolidated_last_participant_id;
        cta_output::consolidated_last_price consolidated_last_price;
        cta_output::consolidated_high_price consolidated_high_price;
        cta_output::consolidated_low_price consolidated_low_price;
        cta_output::consolidated_total_volume consolidated_total_volume;
        cta_output::consolidated_tick consolidated_tick;
        cta_output::participant_previous_close_price_date participant_previous_close_price_date;
        cta_output::participant_last_price participant_last_price;
        cta_output::participant_high_price participant_high_price;
        cta_output::participant_low_price participant_low_price;
        cta_output::participant_open_price participant_open_price;
        cta_output::participant_total_volume participant_total_volume;
        cta_output::participant_tick participant_tick;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::trade;
    cta_output::trade_message_type trade_message_type = cta_output::trade_message_type::enum_type::trade_cancel_error;

    fields_type fields;

    // parse method
    static trade_cancel_error_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_cancel_error_message*>(buffer);
    }

    // parse method const
    static const trade_cancel_error_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_cancel_error_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_cancel_error_message::fields_type, participant_id) == 0, "unexpected offset of trade_cancel_error_message::fields_type::participant_id");
static_assert(offsetof(trade_cancel_error_message::fields_type, timestamp_1) == 1, "unexpected offset of trade_cancel_error_message::fields_type::timestamp_1");
static_assert(offsetof(trade_cancel_error_message::fields_type, message_id) == 9, "unexpected offset of trade_cancel_error_message::fields_type::message_id");
static_assert(offsetof(trade_cancel_error_message::fields_type, transaction_id) == 10, "unexpected offset of trade_cancel_error_message::fields_type::transaction_id");
static_assert(offsetof(trade_cancel_error_message::fields_type, participant_reference_number) == 14, "unexpected offset of trade_cancel_error_message::fields_type::participant_reference_number");
static_assert(offsetof(trade_cancel_error_message::fields_type, security_symbol) == 22, "unexpected offset of trade_cancel_error_message::fields_type::security_symbol");
static_assert(offsetof(trade_cancel_error_message::fields_type, instrument_type) == 33, "unexpected offset of trade_cancel_error_message::fields_type::instrument_type");
static_assert(offsetof(trade_cancel_error_message::fields_type, sale_condition_4) == 34, "unexpected offset of trade_cancel_error_message::fields_type::sale_condition_4");
static_assert(offsetof(trade_cancel_error_message::fields_type, trade_price) == 38, "unexpected offset of trade_cancel_error_message::fields_type::trade_price");
static_assert(offsetof(trade_cancel_error_message::fields_type, trade_volume) == 46, "unexpected offset of trade_cancel_error_message::fields_type::trade_volume");
static_assert(offsetof(trade_cancel_error_message::fields_type, sellers_sale_days) == 50, "unexpected offset of trade_cancel_error_message::fields_type::sellers_sale_days");
static_assert(offsetof(trade_cancel_error_message::fields_type, stop_stock_indicator) == 51, "unexpected offset of trade_cancel_error_message::fields_type::stop_stock_indicator");
static_assert(offsetof(trade_cancel_error_message::fields_type, trade_through_exempt_indicator) == 52, "unexpected offset of trade_cancel_error_message::fields_type::trade_through_exempt_indicator");
static_assert(offsetof(trade_cancel_error_message::fields_type, trade_reporting_facility_id) == 53, "unexpected offset of trade_cancel_error_message::fields_type::trade_reporting_facility_id");
static_assert(offsetof(trade_cancel_error_message::fields_type, original_participant_reference_number) == 54, "unexpected offset of trade_cancel_error_message::fields_type::original_participant_reference_number");
static_assert(offsetof(trade_cancel_error_message::fields_type, timestamp_2) == 62, "unexpected offset of trade_cancel_error_message::fields_type::timestamp_2");
static_assert(offsetof(trade_cancel_error_message::fields_type, cancel_error_action) == 70, "unexpected offset of trade_cancel_error_message::fields_type::cancel_error_action");
static_assert(offsetof(trade_cancel_error_message::fields_type, short_sale_restriction_indicator) == 71, "unexpected offset of trade_cancel_error_message::fields_type::short_sale_restriction_indicator");
static_assert(offsetof(trade_cancel_error_message::fields_type, primary_listing_market_participant_id) == 72, "unexpected offset of trade_cancel_error_message::fields_type::primary_listing_market_participant_id");
static_assert(offsetof(trade_cancel_error_message::fields_type, financial_status_indicator) == 73, "unexpected offset of trade_cancel_error_message::fields_type::financial_status_indicator");
static_assert(offsetof(trade_cancel_error_message::fields_type, consolidated_previous_close_price_date) == 74, "unexpected offset of trade_cancel_error_message::fields_type::consolidated_previous_close_price_date");
static_assert(offsetof(trade_cancel_error_message::fields_type, consolidated_last_participant_id) == 78, "unexpected offset of trade_cancel_error_message::fields_type::consolidated_last_participant_id");
static_assert(offsetof(trade_cancel_error_message::fields_type, consolidated_last_price) == 79, "unexpected offset of trade_cancel_error_message::fields_type::consolidated_last_price");
static_assert(offsetof(trade_cancel_error_message::fields_type, consolidated_high_price) == 87, "unexpected offset of trade_cancel_error_message::fields_type::consolidated_high_price");
static_assert(offsetof(trade_cancel_error_message::fields_type, consolidated_low_price) == 95, "unexpected offset of trade_cancel_error_message::fields_type::consolidated_low_price");
static_assert(offsetof(trade_cancel_error_message::fields_type, consolidated_total_volume) == 103, "unexpected offset of trade_cancel_error_message::fields_type::consolidated_total_volume");
static_assert(offsetof(trade_cancel_error_message::fields_type, consolidated_tick) == 107, "unexpected offset of trade_cancel_error_message::fields_type::consolidated_tick");
static_assert(offsetof(trade_cancel_error_message::fields_type, participant_previous_close_price_date) == 108, "unexpected offset of trade_cancel_error_message::fields_type::participant_previous_close_price_date");
static_assert(offsetof(trade_cancel_error_message::fields_type, participant_last_price) == 112, "unexpected offset of trade_cancel_error_message::fields_type::participant_last_price");
static_assert(offsetof(trade_cancel_error_message::fields_type, participant_high_price) == 120, "unexpected offset of trade_cancel_error_message::fields_type::participant_high_price");
static_assert(offsetof(trade_cancel_error_message::fields_type, participant_low_price) == 128, "unexpected offset of trade_cancel_error_message::fields_type::participant_low_price");
static_assert(offsetof(trade_cancel_error_message::fields_type, participant_open_price) == 136, "unexpected offset of trade_cancel_error_message::fields_type::participant_open_price");
static_assert(offsetof(trade_cancel_error_message::fields_type, participant_total_volume) == 144, "unexpected offset of trade_cancel_error_message::fields_type::participant_total_volume");
static_assert(offsetof(trade_cancel_error_message::fields_type, participant_tick) == 148, "unexpected offset of trade_cancel_error_message::fields_type::participant_tick");
static_assert(sizeof(trade_cancel_error_message::fields_type) == 149, "unexpected sizeof trade_cancel_error_message::fields_type");
static_assert(sizeof(trade_cancel_error_message) == sizeof(cta_output::block_header) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::trade_message_type) + 149, "unexpected sizeof trade_cancel_error_message");

#pragma pack(pop)
}
