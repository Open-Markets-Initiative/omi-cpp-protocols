#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TradingStatus.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/Reason.hpp"
#include "../types/IexTpHeader.hpp"
#include "../types/IexTpMessageBlockLength.hpp"
#include "../types/IexTpMessageLength.hpp"
#include "../types/IexTpMessageType.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

namespace snap_deep = ::iex::iexequities::deep::snap::v1_6;

#pragma pack(push, 1)

// Trading Status Message
struct trading_status_message {

    struct fields_type {
        snap_deep::trading_status trading_status;
        snap_deep::timestamp timestamp;
        snap_deep::symbol symbol;
        snap_deep::reason reason;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) + sizeof(snap_deep::iex_tp_header) + sizeof(snap_deep::iex_tp_message_block_length) + sizeof(snap_deep::iex_tp_message_length) + sizeof(snap_deep::iex_tp_message_type) - 2), message_type::enum_type::snapshot_data_message};
    snap_deep::iex_tp_header iex_tp_header;
    snap_deep::iex_tp_message_block_length iex_tp_message_block_length;
    snap_deep::iex_tp_message_length iex_tp_message_length;
    snap_deep::iex_tp_message_type iex_tp_message_type = snap_deep::iex_tp_message_type::enum_type::trading_status_message;

    fields_type fields;

    // parse method
    static trading_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<trading_status_message*>(buffer);
    }

    // parse method const
    static const trading_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trading_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trading_status_message::fields_type, trading_status) == 0, "unexpected offset of trading_status_message::fields_type::trading_status");
static_assert(offsetof(trading_status_message::fields_type, timestamp) == 1, "unexpected offset of trading_status_message::fields_type::timestamp");
static_assert(offsetof(trading_status_message::fields_type, symbol) == 9, "unexpected offset of trading_status_message::fields_type::symbol");
static_assert(offsetof(trading_status_message::fields_type, reason) == 17, "unexpected offset of trading_status_message::fields_type::reason");
static_assert(sizeof(trading_status_message::fields_type) == 21, "unexpected sizeof trading_status_message::fields_type");
static_assert(sizeof(trading_status_message) == sizeof(message_header) + sizeof(snap_deep::iex_tp_header) + sizeof(snap_deep::iex_tp_message_block_length) + sizeof(snap_deep::iex_tp_message_length) + sizeof(snap_deep::iex_tp_message_type) + 21, "unexpected sizeof trading_status_message");

#pragma pack(pop)
}
