#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SaleConditionFlags.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/SizeType.hpp"
#include "../types/Price.hpp"
#include "../types/TradeId.hpp"
#include "../types/IexTpHeader.hpp"
#include "../types/IexTpMessageBlockLength.hpp"
#include "../types/IexTpMessageLength.hpp"
#include "../types/IexTpMessageType.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

namespace snap_deep = ::iex::iexequities::deep::snap::v1_6;

#pragma pack(push, 1)

// Trade Report Message
struct trade_report_message {

    struct fields_type {
        snap_deep::sale_condition_flags sale_condition_flags;
        snap_deep::timestamp timestamp;
        snap_deep::symbol symbol;
        snap_deep::size_type size;
        snap_deep::price price;
        snap_deep::trade_id trade_id;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) + sizeof(snap_deep::iex_tp_header) + sizeof(snap_deep::iex_tp_message_block_length) + sizeof(snap_deep::iex_tp_message_length) + sizeof(snap_deep::iex_tp_message_type) - 2), message_type::enum_type::snapshot_data_message};
    snap_deep::iex_tp_header iex_tp_header;
    snap_deep::iex_tp_message_block_length iex_tp_message_block_length;
    snap_deep::iex_tp_message_length iex_tp_message_length;
    snap_deep::iex_tp_message_type iex_tp_message_type = snap_deep::iex_tp_message_type::enum_type::trade_report_message;

    fields_type fields;

    // parse method
    static trade_report_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_report_message*>(buffer);
    }

    // parse method const
    static const trade_report_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_report_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_report_message::fields_type, sale_condition_flags) == 0, "unexpected offset of trade_report_message::fields_type::sale_condition_flags");
static_assert(offsetof(trade_report_message::fields_type, timestamp) == 1, "unexpected offset of trade_report_message::fields_type::timestamp");
static_assert(offsetof(trade_report_message::fields_type, symbol) == 9, "unexpected offset of trade_report_message::fields_type::symbol");
static_assert(offsetof(trade_report_message::fields_type, size) == 17, "unexpected offset of trade_report_message::fields_type::size");
static_assert(offsetof(trade_report_message::fields_type, price) == 21, "unexpected offset of trade_report_message::fields_type::price");
static_assert(offsetof(trade_report_message::fields_type, trade_id) == 29, "unexpected offset of trade_report_message::fields_type::trade_id");
static_assert(sizeof(trade_report_message::fields_type) == 37, "unexpected sizeof trade_report_message::fields_type");
static_assert(sizeof(trade_report_message) == sizeof(message_header) + sizeof(snap_deep::iex_tp_header) + sizeof(snap_deep::iex_tp_message_block_length) + sizeof(snap_deep::iex_tp_message_length) + sizeof(snap_deep::iex_tp_message_type) + 37, "unexpected sizeof trade_report_message");

#pragma pack(pop)
}
