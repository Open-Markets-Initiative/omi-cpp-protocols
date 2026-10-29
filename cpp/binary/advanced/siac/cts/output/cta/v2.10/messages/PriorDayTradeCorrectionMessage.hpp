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
#include "../structs/PriorDayCorrectedTrade.hpp"
#include "../types/TradeReportingFacilityId.hpp"
#include "../structs/PriorDayOriginalTrade.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/PriorDayMessageType.hpp"

namespace siac::cts::output::cta::v2_10 {

namespace cta_output = ::siac::cts::output::cta::v2_10;

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
        cta_output::prior_day_corrected_trade prior_day_corrected_trade;
        cta_output::trade_reporting_facility_id trade_reporting_facility_id;
        cta_output::prior_day_original_trade prior_day_original_trade;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::prior_day;
    cta_output::prior_day_message_type prior_day_message_type = cta_output::prior_day_message_type::enum_type::prior_day_trade_correction_message;

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
static_assert(offsetof(prior_day_trade_correction_message::fields_type, prior_day_corrected_trade) == 34, "unexpected offset of prior_day_trade_correction_message::fields_type::prior_day_corrected_trade");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, trade_reporting_facility_id) == 62, "unexpected offset of prior_day_trade_correction_message::fields_type::trade_reporting_facility_id");
static_assert(offsetof(prior_day_trade_correction_message::fields_type, prior_day_original_trade) == 63, "unexpected offset of prior_day_trade_correction_message::fields_type::prior_day_original_trade");
static_assert(sizeof(prior_day_trade_correction_message::fields_type) == 91, "unexpected sizeof prior_day_trade_correction_message::fields_type");
static_assert(sizeof(prior_day_trade_correction_message) == sizeof(cta_output::block_header) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::prior_day_message_type) + 91, "unexpected sizeof prior_day_trade_correction_message");

#pragma pack(pop)
}
