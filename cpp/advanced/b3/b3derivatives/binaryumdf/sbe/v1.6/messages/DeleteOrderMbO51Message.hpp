#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/Offset9Padding1.hpp"
#include "../types/MdEntryType.hpp"
#include "../types/Offset11Padding1.hpp"
#include "../types/MdEntryPositionNo.hpp"
#include "../types/MdEntrySizeQuantityOptional.hpp"
#include "../types/SecondaryOrderId.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_6;

#pragma pack(push, 1)

// Delete Order Mb O 51 Message
struct delete_order_mb_o_51_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::offset_9_padding_1 offset_9_padding_1;
        sbe_binaryumdf::md_entry_type md_entry_type;
        sbe_binaryumdf::offset_11_padding_1 offset_11_padding_1;
        sbe_binaryumdf::md_entry_position_no md_entry_position_no;
        sbe_binaryumdf::md_entry_size_quantity_optional md_entry_size_quantity_optional;
        sbe_binaryumdf::secondary_order_id secondary_order_id;
        sbe_binaryumdf::md_entry_timestamp md_entry_timestamp;
        sbe_binaryumdf::rpt_seq rpt_seq;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static delete_order_mb_o_51_message* parse(std::byte* buffer) {
        return reinterpret_cast<delete_order_mb_o_51_message*>(buffer);
    }

    // parse method const
    static const delete_order_mb_o_51_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const delete_order_mb_o_51_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(delete_order_mb_o_51_message::fields_type, security_id) == 0, "unexpected offset of delete_order_mb_o_51_message::fields_type::security_id");
static_assert(offsetof(delete_order_mb_o_51_message::fields_type, match_event_indicator) == 8, "unexpected offset of delete_order_mb_o_51_message::fields_type::match_event_indicator");
static_assert(offsetof(delete_order_mb_o_51_message::fields_type, offset_9_padding_1) == 9, "unexpected offset of delete_order_mb_o_51_message::fields_type::offset_9_padding_1");
static_assert(offsetof(delete_order_mb_o_51_message::fields_type, md_entry_type) == 10, "unexpected offset of delete_order_mb_o_51_message::fields_type::md_entry_type");
static_assert(offsetof(delete_order_mb_o_51_message::fields_type, offset_11_padding_1) == 11, "unexpected offset of delete_order_mb_o_51_message::fields_type::offset_11_padding_1");
static_assert(offsetof(delete_order_mb_o_51_message::fields_type, md_entry_position_no) == 12, "unexpected offset of delete_order_mb_o_51_message::fields_type::md_entry_position_no");
static_assert(offsetof(delete_order_mb_o_51_message::fields_type, md_entry_size_quantity_optional) == 16, "unexpected offset of delete_order_mb_o_51_message::fields_type::md_entry_size_quantity_optional");
static_assert(offsetof(delete_order_mb_o_51_message::fields_type, secondary_order_id) == 24, "unexpected offset of delete_order_mb_o_51_message::fields_type::secondary_order_id");
static_assert(offsetof(delete_order_mb_o_51_message::fields_type, md_entry_timestamp) == 32, "unexpected offset of delete_order_mb_o_51_message::fields_type::md_entry_timestamp");
static_assert(offsetof(delete_order_mb_o_51_message::fields_type, rpt_seq) == 40, "unexpected offset of delete_order_mb_o_51_message::fields_type::rpt_seq");
static_assert(sizeof(delete_order_mb_o_51_message::fields_type) == 44, "unexpected sizeof delete_order_mb_o_51_message::fields_type");
static_assert(sizeof(delete_order_mb_o_51_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 44, "unexpected sizeof delete_order_mb_o_51_message");

#pragma pack(pop)
}
