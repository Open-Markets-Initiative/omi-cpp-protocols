#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/TradeDate.hpp"
#include "../types/MdCorporateOffsetPriceOptional.hpp"
#include "../types/MdEntrySizeQuantityOptional.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_6;

#pragma pack(push, 1)

// Theoretical Opening Price 16 Message
struct theoretical_opening_price_16_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::md_update_action md_update_action;
        sbe_binaryumdf::trade_date trade_date;
        sbe_binaryumdf::md_corporate_offset_price_optional md_corporate_offset_price_optional;
        sbe_binaryumdf::md_entry_size_quantity_optional md_entry_size_quantity_optional;
        sbe_binaryumdf::md_entry_timestamp md_entry_timestamp;
        sbe_binaryumdf::rpt_seq rpt_seq;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static theoretical_opening_price_16_message* parse(std::byte* buffer) {
        return reinterpret_cast<theoretical_opening_price_16_message*>(buffer);
    }

    // parse method const
    static const theoretical_opening_price_16_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const theoretical_opening_price_16_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(theoretical_opening_price_16_message::fields_type, security_id) == 0, "unexpected offset of theoretical_opening_price_16_message::fields_type::security_id");
static_assert(offsetof(theoretical_opening_price_16_message::fields_type, match_event_indicator) == 8, "unexpected offset of theoretical_opening_price_16_message::fields_type::match_event_indicator");
static_assert(offsetof(theoretical_opening_price_16_message::fields_type, md_update_action) == 9, "unexpected offset of theoretical_opening_price_16_message::fields_type::md_update_action");
static_assert(offsetof(theoretical_opening_price_16_message::fields_type, trade_date) == 10, "unexpected offset of theoretical_opening_price_16_message::fields_type::trade_date");
static_assert(offsetof(theoretical_opening_price_16_message::fields_type, md_corporate_offset_price_optional) == 12, "unexpected offset of theoretical_opening_price_16_message::fields_type::md_corporate_offset_price_optional");
static_assert(offsetof(theoretical_opening_price_16_message::fields_type, md_entry_size_quantity_optional) == 20, "unexpected offset of theoretical_opening_price_16_message::fields_type::md_entry_size_quantity_optional");
static_assert(offsetof(theoretical_opening_price_16_message::fields_type, md_entry_timestamp) == 28, "unexpected offset of theoretical_opening_price_16_message::fields_type::md_entry_timestamp");
static_assert(offsetof(theoretical_opening_price_16_message::fields_type, rpt_seq) == 36, "unexpected offset of theoretical_opening_price_16_message::fields_type::rpt_seq");
static_assert(sizeof(theoretical_opening_price_16_message::fields_type) == 40, "unexpected sizeof theoretical_opening_price_16_message::fields_type");
static_assert(sizeof(theoretical_opening_price_16_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 40, "unexpected sizeof theoretical_opening_price_16_message");

#pragma pack(pop)
}
