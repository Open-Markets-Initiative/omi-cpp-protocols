#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/Offset9Padding1.hpp"
#include "../types/TradeDate.hpp"
#include "../types/MdEntrySizeQuantity.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_8;

#pragma pack(push, 1)

// Open Interest 29 Message
struct open_interest_29_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::offset_9_padding_1 offset_9_padding_1;
        sbe_binaryumdf::trade_date trade_date;
        sbe_binaryumdf::md_entry_size_quantity md_entry_size_quantity;
        sbe_binaryumdf::md_entry_timestamp md_entry_timestamp;
        sbe_binaryumdf::rpt_seq rpt_seq;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static open_interest_29_message* parse(std::byte* buffer) {
        return reinterpret_cast<open_interest_29_message*>(buffer);
    }

    // parse method const
    static const open_interest_29_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const open_interest_29_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(open_interest_29_message::fields_type, security_id) == 0, "unexpected offset of open_interest_29_message::fields_type::security_id");
static_assert(offsetof(open_interest_29_message::fields_type, match_event_indicator) == 8, "unexpected offset of open_interest_29_message::fields_type::match_event_indicator");
static_assert(offsetof(open_interest_29_message::fields_type, offset_9_padding_1) == 9, "unexpected offset of open_interest_29_message::fields_type::offset_9_padding_1");
static_assert(offsetof(open_interest_29_message::fields_type, trade_date) == 10, "unexpected offset of open_interest_29_message::fields_type::trade_date");
static_assert(offsetof(open_interest_29_message::fields_type, md_entry_size_quantity) == 12, "unexpected offset of open_interest_29_message::fields_type::md_entry_size_quantity");
static_assert(offsetof(open_interest_29_message::fields_type, md_entry_timestamp) == 20, "unexpected offset of open_interest_29_message::fields_type::md_entry_timestamp");
static_assert(offsetof(open_interest_29_message::fields_type, rpt_seq) == 28, "unexpected offset of open_interest_29_message::fields_type::rpt_seq");
static_assert(sizeof(open_interest_29_message::fields_type) == 32, "unexpected sizeof open_interest_29_message::fields_type");
static_assert(sizeof(open_interest_29_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 32, "unexpected sizeof open_interest_29_message");

#pragma pack(pop)
}
