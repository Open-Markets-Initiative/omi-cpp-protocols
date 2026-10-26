#pragma once

#include <cstddef>
#include "../structs/BlockHeader.hpp"
#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol5.hpp"
#include "../types/SaleCondition1.hpp"
#include "../types/SaleConditionCategory.hpp"
#include "../types/TradePrice2.hpp"
#include "../types/FractionalTradeVolume4.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/ConsolidatedHighLowLastIndicator.hpp"
#include "../types/ParticipantOpenHighLowLastIndicator.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/TradeMessageType.hpp"

namespace siac::cts::output::cta::v2_11_b {

namespace cta_output = ::siac::cts::output::cta::v2_11_b;

#pragma pack(push, 1)

// Fractional Short Trade Message
struct fractional_short_trade_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::timestamp_1 timestamp_1;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::security_symbol_5 security_symbol_5;
        cta_output::sale_condition_1 sale_condition_1;
        cta_output::sale_condition_category sale_condition_category;
        cta_output::trade_price_2 trade_price_2;
        cta_output::fractional_trade_volume_4 fractional_trade_volume_4;
        cta_output::primary_listing_market_participant_id primary_listing_market_participant_id;
        cta_output::consolidated_high_low_last_indicator consolidated_high_low_last_indicator;
        cta_output::participant_open_high_low_last_indicator participant_open_high_low_last_indicator;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::trade;
    cta_output::trade_message_type trade_message_type = cta_output::trade_message_type::enum_type::fractional_short_trade;

    fields_type fields;

    // parse method
    static fractional_short_trade_message* parse(std::byte* buffer) {
        return reinterpret_cast<fractional_short_trade_message*>(buffer);
    }

    // parse method const
    static const fractional_short_trade_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const fractional_short_trade_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(fractional_short_trade_message::fields_type, participant_id) == 0, "unexpected offset of fractional_short_trade_message::fields_type::participant_id");
static_assert(offsetof(fractional_short_trade_message::fields_type, timestamp_1) == 1, "unexpected offset of fractional_short_trade_message::fields_type::timestamp_1");
static_assert(offsetof(fractional_short_trade_message::fields_type, message_id) == 9, "unexpected offset of fractional_short_trade_message::fields_type::message_id");
static_assert(offsetof(fractional_short_trade_message::fields_type, transaction_id) == 10, "unexpected offset of fractional_short_trade_message::fields_type::transaction_id");
static_assert(offsetof(fractional_short_trade_message::fields_type, participant_reference_number) == 14, "unexpected offset of fractional_short_trade_message::fields_type::participant_reference_number");
static_assert(offsetof(fractional_short_trade_message::fields_type, security_symbol_5) == 22, "unexpected offset of fractional_short_trade_message::fields_type::security_symbol_5");
static_assert(offsetof(fractional_short_trade_message::fields_type, sale_condition_1) == 27, "unexpected offset of fractional_short_trade_message::fields_type::sale_condition_1");
static_assert(offsetof(fractional_short_trade_message::fields_type, sale_condition_category) == 28, "unexpected offset of fractional_short_trade_message::fields_type::sale_condition_category");
static_assert(offsetof(fractional_short_trade_message::fields_type, trade_price_2) == 29, "unexpected offset of fractional_short_trade_message::fields_type::trade_price_2");
static_assert(offsetof(fractional_short_trade_message::fields_type, fractional_trade_volume_4) == 31, "unexpected offset of fractional_short_trade_message::fields_type::fractional_trade_volume_4");
static_assert(offsetof(fractional_short_trade_message::fields_type, primary_listing_market_participant_id) == 35, "unexpected offset of fractional_short_trade_message::fields_type::primary_listing_market_participant_id");
static_assert(offsetof(fractional_short_trade_message::fields_type, consolidated_high_low_last_indicator) == 36, "unexpected offset of fractional_short_trade_message::fields_type::consolidated_high_low_last_indicator");
static_assert(offsetof(fractional_short_trade_message::fields_type, participant_open_high_low_last_indicator) == 37, "unexpected offset of fractional_short_trade_message::fields_type::participant_open_high_low_last_indicator");
static_assert(sizeof(fractional_short_trade_message::fields_type) == 38, "unexpected sizeof fractional_short_trade_message::fields_type");
static_assert(sizeof(fractional_short_trade_message) == sizeof(cta_output::block_header) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::trade_message_type) + 38, "unexpected sizeof fractional_short_trade_message");

#pragma pack(pop)
}
