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
#include "../types/LastParticipantId.hpp"
#include "../types/PreviousClosePriceDate.hpp"
#include "../types/LastPrice.hpp"
#include "../types/HighPrice.hpp"
#include "../types/LowPrice.hpp"
#include "../types/TotalVolume.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/NumberOfParticipants.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/SummaryMessageType.hpp"

namespace siac::cts::output::cta::v2_10 {

namespace cta_output = ::siac::cts::output::cta::v2_10;

#pragma pack(push, 1)

// Consolidated End Of Day Summary Message
struct consolidated_end_of_day_summary_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::timestamp_1 timestamp_1;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::security_symbol security_symbol;
        cta_output::instrument_type instrument_type;
        cta_output::last_participant_id last_participant_id;
        cta_output::previous_close_price_date previous_close_price_date;
        cta_output::last_price last_price;
        cta_output::high_price high_price;
        cta_output::low_price low_price;
        cta_output::total_volume total_volume;
        cta_output::short_sale_restriction_indicator short_sale_restriction_indicator;
        cta_output::primary_listing_market_participant_id primary_listing_market_participant_id;
        cta_output::financial_status_indicator financial_status_indicator;
        cta_output::number_of_participants number_of_participants;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::summary;
    cta_output::summary_message_type summary_message_type = cta_output::summary_message_type::enum_type::consolidated_end_of_day_summary_message;

    fields_type fields;

    // parse method
    static consolidated_end_of_day_summary_message* parse(std::byte* buffer) {
        return reinterpret_cast<consolidated_end_of_day_summary_message*>(buffer);
    }

    // parse method const
    static const consolidated_end_of_day_summary_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const consolidated_end_of_day_summary_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(consolidated_end_of_day_summary_message::fields_type, participant_id) == 0, "unexpected offset of consolidated_end_of_day_summary_message::fields_type::participant_id");
static_assert(offsetof(consolidated_end_of_day_summary_message::fields_type, timestamp_1) == 1, "unexpected offset of consolidated_end_of_day_summary_message::fields_type::timestamp_1");
static_assert(offsetof(consolidated_end_of_day_summary_message::fields_type, message_id) == 9, "unexpected offset of consolidated_end_of_day_summary_message::fields_type::message_id");
static_assert(offsetof(consolidated_end_of_day_summary_message::fields_type, transaction_id) == 10, "unexpected offset of consolidated_end_of_day_summary_message::fields_type::transaction_id");
static_assert(offsetof(consolidated_end_of_day_summary_message::fields_type, participant_reference_number) == 14, "unexpected offset of consolidated_end_of_day_summary_message::fields_type::participant_reference_number");
static_assert(offsetof(consolidated_end_of_day_summary_message::fields_type, security_symbol) == 22, "unexpected offset of consolidated_end_of_day_summary_message::fields_type::security_symbol");
static_assert(offsetof(consolidated_end_of_day_summary_message::fields_type, instrument_type) == 33, "unexpected offset of consolidated_end_of_day_summary_message::fields_type::instrument_type");
static_assert(offsetof(consolidated_end_of_day_summary_message::fields_type, last_participant_id) == 34, "unexpected offset of consolidated_end_of_day_summary_message::fields_type::last_participant_id");
static_assert(offsetof(consolidated_end_of_day_summary_message::fields_type, previous_close_price_date) == 35, "unexpected offset of consolidated_end_of_day_summary_message::fields_type::previous_close_price_date");
static_assert(offsetof(consolidated_end_of_day_summary_message::fields_type, last_price) == 39, "unexpected offset of consolidated_end_of_day_summary_message::fields_type::last_price");
static_assert(offsetof(consolidated_end_of_day_summary_message::fields_type, high_price) == 47, "unexpected offset of consolidated_end_of_day_summary_message::fields_type::high_price");
static_assert(offsetof(consolidated_end_of_day_summary_message::fields_type, low_price) == 55, "unexpected offset of consolidated_end_of_day_summary_message::fields_type::low_price");
static_assert(offsetof(consolidated_end_of_day_summary_message::fields_type, total_volume) == 63, "unexpected offset of consolidated_end_of_day_summary_message::fields_type::total_volume");
static_assert(offsetof(consolidated_end_of_day_summary_message::fields_type, short_sale_restriction_indicator) == 71, "unexpected offset of consolidated_end_of_day_summary_message::fields_type::short_sale_restriction_indicator");
static_assert(offsetof(consolidated_end_of_day_summary_message::fields_type, primary_listing_market_participant_id) == 72, "unexpected offset of consolidated_end_of_day_summary_message::fields_type::primary_listing_market_participant_id");
static_assert(offsetof(consolidated_end_of_day_summary_message::fields_type, financial_status_indicator) == 73, "unexpected offset of consolidated_end_of_day_summary_message::fields_type::financial_status_indicator");
static_assert(offsetof(consolidated_end_of_day_summary_message::fields_type, number_of_participants) == 74, "unexpected offset of consolidated_end_of_day_summary_message::fields_type::number_of_participants");
static_assert(sizeof(consolidated_end_of_day_summary_message::fields_type) == 75, "unexpected sizeof consolidated_end_of_day_summary_message::fields_type");
static_assert(sizeof(consolidated_end_of_day_summary_message) == sizeof(cta_output::block_header) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::summary_message_type) + 75, "unexpected sizeof consolidated_end_of_day_summary_message");

#pragma pack(pop)
}
