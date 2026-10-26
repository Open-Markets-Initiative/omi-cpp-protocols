#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/MdEntryType.hpp"
#include "../types/Offset11Padding1.hpp"
#include "../types/MdCorporateOffsetPriceOptional.hpp"
#include "../types/MdEntrySizeQuantity.hpp"
#include "../types/MdEntryPositionNo.hpp"
#include "../types/EnteringFirm.hpp"
#include "../types/MdInsertTimestamp.hpp"
#include "../types/SecondaryOrderId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/TransactTime.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_1;

#pragma pack(push, 1)

// Order Mb O 50 Message
struct order_mb_o_50_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::md_update_action md_update_action;
        sbe_binaryumdf::md_entry_type md_entry_type;
        sbe_binaryumdf::offset_11_padding_1 offset_11_padding_1;
        sbe_binaryumdf::md_corporate_offset_price_optional md_corporate_offset_price_optional;
        sbe_binaryumdf::md_entry_size_quantity md_entry_size_quantity;
        sbe_binaryumdf::md_entry_position_no md_entry_position_no;
        sbe_binaryumdf::entering_firm entering_firm;
        sbe_binaryumdf::md_insert_timestamp md_insert_timestamp;
        sbe_binaryumdf::secondary_order_id secondary_order_id;
        sbe_binaryumdf::rpt_seq rpt_seq;
        sbe_binaryumdf::transact_time transact_time;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static order_mb_o_50_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_mb_o_50_message*>(buffer);
    }

    // parse method const
    static const order_mb_o_50_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_mb_o_50_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_mb_o_50_message::fields_type, security_id) == 0, "unexpected offset of order_mb_o_50_message::fields_type::security_id");
static_assert(offsetof(order_mb_o_50_message::fields_type, match_event_indicator) == 8, "unexpected offset of order_mb_o_50_message::fields_type::match_event_indicator");
static_assert(offsetof(order_mb_o_50_message::fields_type, md_update_action) == 9, "unexpected offset of order_mb_o_50_message::fields_type::md_update_action");
static_assert(offsetof(order_mb_o_50_message::fields_type, md_entry_type) == 10, "unexpected offset of order_mb_o_50_message::fields_type::md_entry_type");
static_assert(offsetof(order_mb_o_50_message::fields_type, offset_11_padding_1) == 11, "unexpected offset of order_mb_o_50_message::fields_type::offset_11_padding_1");
static_assert(offsetof(order_mb_o_50_message::fields_type, md_corporate_offset_price_optional) == 12, "unexpected offset of order_mb_o_50_message::fields_type::md_corporate_offset_price_optional");
static_assert(offsetof(order_mb_o_50_message::fields_type, md_entry_size_quantity) == 20, "unexpected offset of order_mb_o_50_message::fields_type::md_entry_size_quantity");
static_assert(offsetof(order_mb_o_50_message::fields_type, md_entry_position_no) == 28, "unexpected offset of order_mb_o_50_message::fields_type::md_entry_position_no");
static_assert(offsetof(order_mb_o_50_message::fields_type, entering_firm) == 32, "unexpected offset of order_mb_o_50_message::fields_type::entering_firm");
static_assert(offsetof(order_mb_o_50_message::fields_type, md_insert_timestamp) == 36, "unexpected offset of order_mb_o_50_message::fields_type::md_insert_timestamp");
static_assert(offsetof(order_mb_o_50_message::fields_type, secondary_order_id) == 44, "unexpected offset of order_mb_o_50_message::fields_type::secondary_order_id");
static_assert(offsetof(order_mb_o_50_message::fields_type, rpt_seq) == 52, "unexpected offset of order_mb_o_50_message::fields_type::rpt_seq");
static_assert(offsetof(order_mb_o_50_message::fields_type, transact_time) == 56, "unexpected offset of order_mb_o_50_message::fields_type::transact_time");
static_assert(sizeof(order_mb_o_50_message::fields_type) == 64, "unexpected sizeof order_mb_o_50_message::fields_type");
static_assert(sizeof(order_mb_o_50_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 64, "unexpected sizeof order_mb_o_50_message");

#pragma pack(pop)
}
