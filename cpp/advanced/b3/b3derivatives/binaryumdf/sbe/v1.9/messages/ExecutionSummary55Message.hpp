#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/Offset8Padding2.hpp"
#include "../types/AggressorSide.hpp"
#include "../types/Offset11Padding1.hpp"
#include "../types/LastPx.hpp"
#include "../types/FillQty.hpp"
#include "../types/TradedHiddenQty.hpp"
#include "../types/CxlQty.hpp"
#include "../types/AggressorTime.hpp"
#include "../types/RptSeq.hpp"
#include "../types/MdEntryTimestamp.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_9;

#pragma pack(push, 1)

// Execution Summary 55 Message
struct execution_summary_55_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::offset_8_padding_2 offset_8_padding_2;
        sbe_binaryumdf::aggressor_side aggressor_side;
        sbe_binaryumdf::offset_11_padding_1 offset_11_padding_1;
        sbe_binaryumdf::last_px last_px;
        sbe_binaryumdf::fill_qty fill_qty;
        sbe_binaryumdf::traded_hidden_qty traded_hidden_qty;
        sbe_binaryumdf::cxl_qty cxl_qty;
        sbe_binaryumdf::aggressor_time aggressor_time;
        sbe_binaryumdf::rpt_seq rpt_seq;
        sbe_binaryumdf::md_entry_timestamp md_entry_timestamp;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static execution_summary_55_message* parse(std::byte* buffer) {
        return reinterpret_cast<execution_summary_55_message*>(buffer);
    }

    // parse method const
    static const execution_summary_55_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const execution_summary_55_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(execution_summary_55_message::fields_type, security_id) == 0, "unexpected offset of execution_summary_55_message::fields_type::security_id");
static_assert(offsetof(execution_summary_55_message::fields_type, offset_8_padding_2) == 8, "unexpected offset of execution_summary_55_message::fields_type::offset_8_padding_2");
static_assert(offsetof(execution_summary_55_message::fields_type, aggressor_side) == 10, "unexpected offset of execution_summary_55_message::fields_type::aggressor_side");
static_assert(offsetof(execution_summary_55_message::fields_type, offset_11_padding_1) == 11, "unexpected offset of execution_summary_55_message::fields_type::offset_11_padding_1");
static_assert(offsetof(execution_summary_55_message::fields_type, last_px) == 12, "unexpected offset of execution_summary_55_message::fields_type::last_px");
static_assert(offsetof(execution_summary_55_message::fields_type, fill_qty) == 20, "unexpected offset of execution_summary_55_message::fields_type::fill_qty");
static_assert(offsetof(execution_summary_55_message::fields_type, traded_hidden_qty) == 28, "unexpected offset of execution_summary_55_message::fields_type::traded_hidden_qty");
static_assert(offsetof(execution_summary_55_message::fields_type, cxl_qty) == 36, "unexpected offset of execution_summary_55_message::fields_type::cxl_qty");
static_assert(offsetof(execution_summary_55_message::fields_type, aggressor_time) == 44, "unexpected offset of execution_summary_55_message::fields_type::aggressor_time");
static_assert(offsetof(execution_summary_55_message::fields_type, rpt_seq) == 52, "unexpected offset of execution_summary_55_message::fields_type::rpt_seq");
static_assert(offsetof(execution_summary_55_message::fields_type, md_entry_timestamp) == 56, "unexpected offset of execution_summary_55_message::fields_type::md_entry_timestamp");
static_assert(sizeof(execution_summary_55_message::fields_type) == 64, "unexpected sizeof execution_summary_55_message::fields_type");
static_assert(sizeof(execution_summary_55_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 64, "unexpected sizeof execution_summary_55_message");

#pragma pack(pop)
}
