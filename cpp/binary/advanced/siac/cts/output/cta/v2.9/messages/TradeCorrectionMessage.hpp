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
#include "../structs/CorrectedTrade.hpp"
#include "../types/TradeReportingFacilityId.hpp"
#include "../types/Timestamp2Optional.hpp"
#include "../types/OriginalParticipantReferenceNumber.hpp"
#include "../structs/OriginalTrade.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../structs/ConsolidatedData.hpp"
#include "../structs/ParticipantData.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/TradeMessageType.hpp"

namespace siac::cts::output::cta::v2_9 {

namespace cta_output = ::siac::cts::output::cta::v2_9;

#pragma pack(push, 1)

// Trade Correction Message
struct trade_correction_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::timestamp_1 timestamp_1;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::security_symbol security_symbol;
        cta_output::instrument_type instrument_type;
        cta_output::corrected_trade corrected_trade;
        cta_output::trade_reporting_facility_id trade_reporting_facility_id;
        cta_output::timestamp_2_optional timestamp_2;
        cta_output::original_participant_reference_number original_participant_reference_number;
        cta_output::original_trade original_trade;
        cta_output::primary_listing_market_participant_id primary_listing_market_participant_id;
        cta_output::financial_status_indicator financial_status_indicator;
        cta_output::consolidated_data consolidated_data;
        cta_output::participant_data participant_data;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::trade;
    cta_output::trade_message_type trade_message_type = cta_output::trade_message_type::enum_type::trade_correction_message;

    fields_type fields;

    // parse method
    static trade_correction_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_correction_message*>(buffer);
    }

    // parse method const
    static const trade_correction_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_correction_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_correction_message::fields_type, participant_id) == 0, "unexpected offset of trade_correction_message::fields_type::participant_id");
static_assert(offsetof(trade_correction_message::fields_type, timestamp_1) == 1, "unexpected offset of trade_correction_message::fields_type::timestamp_1");
static_assert(offsetof(trade_correction_message::fields_type, message_id) == 9, "unexpected offset of trade_correction_message::fields_type::message_id");
static_assert(offsetof(trade_correction_message::fields_type, transaction_id) == 10, "unexpected offset of trade_correction_message::fields_type::transaction_id");
static_assert(offsetof(trade_correction_message::fields_type, participant_reference_number) == 14, "unexpected offset of trade_correction_message::fields_type::participant_reference_number");
static_assert(offsetof(trade_correction_message::fields_type, security_symbol) == 22, "unexpected offset of trade_correction_message::fields_type::security_symbol");
static_assert(offsetof(trade_correction_message::fields_type, instrument_type) == 33, "unexpected offset of trade_correction_message::fields_type::instrument_type");
static_assert(offsetof(trade_correction_message::fields_type, corrected_trade) == 34, "unexpected offset of trade_correction_message::fields_type::corrected_trade");
static_assert(offsetof(trade_correction_message::fields_type, trade_reporting_facility_id) == 62, "unexpected offset of trade_correction_message::fields_type::trade_reporting_facility_id");
static_assert(offsetof(trade_correction_message::fields_type, timestamp_2) == 63, "unexpected offset of trade_correction_message::fields_type::timestamp_2");
static_assert(offsetof(trade_correction_message::fields_type, original_participant_reference_number) == 71, "unexpected offset of trade_correction_message::fields_type::original_participant_reference_number");
static_assert(offsetof(trade_correction_message::fields_type, original_trade) == 79, "unexpected offset of trade_correction_message::fields_type::original_trade");
static_assert(offsetof(trade_correction_message::fields_type, primary_listing_market_participant_id) == 107, "unexpected offset of trade_correction_message::fields_type::primary_listing_market_participant_id");
static_assert(offsetof(trade_correction_message::fields_type, financial_status_indicator) == 108, "unexpected offset of trade_correction_message::fields_type::financial_status_indicator");
static_assert(offsetof(trade_correction_message::fields_type, consolidated_data) == 109, "unexpected offset of trade_correction_message::fields_type::consolidated_data");
static_assert(offsetof(trade_correction_message::fields_type, participant_data) == 143, "unexpected offset of trade_correction_message::fields_type::participant_data");
static_assert(sizeof(trade_correction_message::fields_type) == 184, "unexpected sizeof trade_correction_message::fields_type");
static_assert(sizeof(trade_correction_message) == sizeof(cta_output::block_header) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::trade_message_type) + 184, "unexpected sizeof trade_correction_message");

#pragma pack(pop)
}
