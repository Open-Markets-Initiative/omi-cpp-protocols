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
#include "../structs/FractionalCorrectedTrade.hpp"
#include "../types/TradeReportingFacilityId.hpp"
#include "../types/Timestamp2Optional.hpp"
#include "../types/OriginalParticipantReferenceNumber.hpp"
#include "../structs/FractionalOriginalTrade.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../structs/FractionalConsolidatedData.hpp"
#include "../structs/FractionalParticipantData.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/TradeMessageType.hpp"

namespace siac::cts::output::cta::v2_10 {

namespace cta_output = ::siac::cts::output::cta::v2_10;

#pragma pack(push, 1)

// Fractional Trade Correction Message
struct fractional_trade_correction_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::timestamp_1 timestamp_1;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::security_symbol security_symbol;
        cta_output::instrument_type instrument_type;
        cta_output::fractional_corrected_trade fractional_corrected_trade;
        cta_output::trade_reporting_facility_id trade_reporting_facility_id;
        cta_output::timestamp_2_optional timestamp_2;
        cta_output::original_participant_reference_number original_participant_reference_number;
        cta_output::fractional_original_trade fractional_original_trade;
        cta_output::primary_listing_market_participant_id primary_listing_market_participant_id;
        cta_output::financial_status_indicator financial_status_indicator;
        cta_output::fractional_consolidated_data fractional_consolidated_data;
        cta_output::fractional_participant_data fractional_participant_data;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::trade;
    cta_output::trade_message_type trade_message_type = cta_output::trade_message_type::enum_type::fractional_trade_correction_message;

    fields_type fields;

    // parse method
    static fractional_trade_correction_message* parse(std::byte* buffer) {
        return reinterpret_cast<fractional_trade_correction_message*>(buffer);
    }

    // parse method const
    static const fractional_trade_correction_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const fractional_trade_correction_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(fractional_trade_correction_message::fields_type, participant_id) == 0, "unexpected offset of fractional_trade_correction_message::fields_type::participant_id");
static_assert(offsetof(fractional_trade_correction_message::fields_type, timestamp_1) == 1, "unexpected offset of fractional_trade_correction_message::fields_type::timestamp_1");
static_assert(offsetof(fractional_trade_correction_message::fields_type, message_id) == 9, "unexpected offset of fractional_trade_correction_message::fields_type::message_id");
static_assert(offsetof(fractional_trade_correction_message::fields_type, transaction_id) == 10, "unexpected offset of fractional_trade_correction_message::fields_type::transaction_id");
static_assert(offsetof(fractional_trade_correction_message::fields_type, participant_reference_number) == 14, "unexpected offset of fractional_trade_correction_message::fields_type::participant_reference_number");
static_assert(offsetof(fractional_trade_correction_message::fields_type, security_symbol) == 22, "unexpected offset of fractional_trade_correction_message::fields_type::security_symbol");
static_assert(offsetof(fractional_trade_correction_message::fields_type, instrument_type) == 33, "unexpected offset of fractional_trade_correction_message::fields_type::instrument_type");
static_assert(offsetof(fractional_trade_correction_message::fields_type, fractional_corrected_trade) == 34, "unexpected offset of fractional_trade_correction_message::fields_type::fractional_corrected_trade");
static_assert(offsetof(fractional_trade_correction_message::fields_type, trade_reporting_facility_id) == 58, "unexpected offset of fractional_trade_correction_message::fields_type::trade_reporting_facility_id");
static_assert(offsetof(fractional_trade_correction_message::fields_type, timestamp_2) == 59, "unexpected offset of fractional_trade_correction_message::fields_type::timestamp_2");
static_assert(offsetof(fractional_trade_correction_message::fields_type, original_participant_reference_number) == 67, "unexpected offset of fractional_trade_correction_message::fields_type::original_participant_reference_number");
static_assert(offsetof(fractional_trade_correction_message::fields_type, fractional_original_trade) == 75, "unexpected offset of fractional_trade_correction_message::fields_type::fractional_original_trade");
static_assert(offsetof(fractional_trade_correction_message::fields_type, primary_listing_market_participant_id) == 99, "unexpected offset of fractional_trade_correction_message::fields_type::primary_listing_market_participant_id");
static_assert(offsetof(fractional_trade_correction_message::fields_type, financial_status_indicator) == 100, "unexpected offset of fractional_trade_correction_message::fields_type::financial_status_indicator");
static_assert(offsetof(fractional_trade_correction_message::fields_type, fractional_consolidated_data) == 101, "unexpected offset of fractional_trade_correction_message::fields_type::fractional_consolidated_data");
static_assert(offsetof(fractional_trade_correction_message::fields_type, fractional_participant_data) == 139, "unexpected offset of fractional_trade_correction_message::fields_type::fractional_participant_data");
static_assert(sizeof(fractional_trade_correction_message::fields_type) == 184, "unexpected sizeof fractional_trade_correction_message::fields_type");
static_assert(sizeof(fractional_trade_correction_message) == sizeof(cta_output::block_header) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::trade_message_type) + 184, "unexpected sizeof fractional_trade_correction_message");

#pragma pack(pop)
}
