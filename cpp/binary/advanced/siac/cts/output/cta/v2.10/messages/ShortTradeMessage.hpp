#pragma once

#include <cstddef>
#include "../structs/BlockHeader.hpp"
#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbolShort.hpp"
#include "../types/SaleCondition.hpp"
#include "../types/SaleConditionCategory.hpp"
#include "../types/TradePriceShort.hpp"
#include "../types/TradeVolumeShort.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/ConsolidatedHighLowLastIndicator.hpp"
#include "../types/ParticipantOpenHighLowLastIndicator.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/TradeMessageType.hpp"

namespace siac::cts::output::cta::v2_10 {

namespace cta_output = ::siac::cts::output::cta::v2_10;

#pragma pack(push, 1)

// Short Trade Message
struct short_trade_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::timestamp_1 timestamp_1;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::security_symbol_short security_symbol_short;
        cta_output::sale_condition sale_condition;
        cta_output::sale_condition_category sale_condition_category;
        cta_output::trade_price_short trade_price_short;
        cta_output::trade_volume_short trade_volume_short;
        cta_output::primary_listing_market_participant_id primary_listing_market_participant_id;
        cta_output::consolidated_high_low_last_indicator consolidated_high_low_last_indicator;
        cta_output::participant_open_high_low_last_indicator participant_open_high_low_last_indicator;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::trade;
    cta_output::trade_message_type trade_message_type = cta_output::trade_message_type::enum_type::short_trade_message;

    fields_type fields;

    // parse method
    static short_trade_message* parse(std::byte* buffer) {
        return reinterpret_cast<short_trade_message*>(buffer);
    }

    // parse method const
    static const short_trade_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const short_trade_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(short_trade_message::fields_type, participant_id) == 0, "unexpected offset of short_trade_message::fields_type::participant_id");
static_assert(offsetof(short_trade_message::fields_type, timestamp_1) == 1, "unexpected offset of short_trade_message::fields_type::timestamp_1");
static_assert(offsetof(short_trade_message::fields_type, message_id) == 9, "unexpected offset of short_trade_message::fields_type::message_id");
static_assert(offsetof(short_trade_message::fields_type, transaction_id) == 10, "unexpected offset of short_trade_message::fields_type::transaction_id");
static_assert(offsetof(short_trade_message::fields_type, participant_reference_number) == 14, "unexpected offset of short_trade_message::fields_type::participant_reference_number");
static_assert(offsetof(short_trade_message::fields_type, security_symbol_short) == 22, "unexpected offset of short_trade_message::fields_type::security_symbol_short");
static_assert(offsetof(short_trade_message::fields_type, sale_condition) == 27, "unexpected offset of short_trade_message::fields_type::sale_condition");
static_assert(offsetof(short_trade_message::fields_type, sale_condition_category) == 28, "unexpected offset of short_trade_message::fields_type::sale_condition_category");
static_assert(offsetof(short_trade_message::fields_type, trade_price_short) == 29, "unexpected offset of short_trade_message::fields_type::trade_price_short");
static_assert(offsetof(short_trade_message::fields_type, trade_volume_short) == 31, "unexpected offset of short_trade_message::fields_type::trade_volume_short");
static_assert(offsetof(short_trade_message::fields_type, primary_listing_market_participant_id) == 33, "unexpected offset of short_trade_message::fields_type::primary_listing_market_participant_id");
static_assert(offsetof(short_trade_message::fields_type, consolidated_high_low_last_indicator) == 34, "unexpected offset of short_trade_message::fields_type::consolidated_high_low_last_indicator");
static_assert(offsetof(short_trade_message::fields_type, participant_open_high_low_last_indicator) == 35, "unexpected offset of short_trade_message::fields_type::participant_open_high_low_last_indicator");
static_assert(sizeof(short_trade_message::fields_type) == 36, "unexpected sizeof short_trade_message::fields_type");
static_assert(sizeof(short_trade_message) == sizeof(cta_output::block_header) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::trade_message_type) + 36, "unexpected sizeof short_trade_message");

#pragma pack(pop)
}
