#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/EventFlags.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/SizeType.hpp"
#include "../types/Price.hpp"
#include "../types/IexTpHeader.hpp"
#include "../types/IexTpMessageBlockLength.hpp"
#include "../types/IexTpMessageLength.hpp"
#include "../types/IexTpMessageType.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

namespace snap_deep = ::iex::iexequities::deep::snap::v1_6;

#pragma pack(push, 1)

// Price Level Sell Update Message
struct price_level_sell_update_message {

    struct fields_type {
        snap_deep::event_flags event_flags;
        snap_deep::timestamp timestamp;
        snap_deep::symbol symbol;
        snap_deep::size_type size;
        snap_deep::price price;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) + sizeof(snap_deep::iex_tp_header) + sizeof(snap_deep::iex_tp_message_block_length) + sizeof(snap_deep::iex_tp_message_length) + sizeof(snap_deep::iex_tp_message_type) - 2), message_type::enum_type::snapshot_data_message};
    snap_deep::iex_tp_header iex_tp_header;
    snap_deep::iex_tp_message_block_length iex_tp_message_block_length;
    snap_deep::iex_tp_message_length iex_tp_message_length;
    snap_deep::iex_tp_message_type iex_tp_message_type = snap_deep::iex_tp_message_type::enum_type::price_level_sell_update_message;

    fields_type fields;

    // parse method
    static price_level_sell_update_message* parse(std::byte* buffer) {
        return reinterpret_cast<price_level_sell_update_message*>(buffer);
    }

    // parse method const
    static const price_level_sell_update_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const price_level_sell_update_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(price_level_sell_update_message::fields_type, event_flags) == 0, "unexpected offset of price_level_sell_update_message::fields_type::event_flags");
static_assert(offsetof(price_level_sell_update_message::fields_type, timestamp) == 1, "unexpected offset of price_level_sell_update_message::fields_type::timestamp");
static_assert(offsetof(price_level_sell_update_message::fields_type, symbol) == 9, "unexpected offset of price_level_sell_update_message::fields_type::symbol");
static_assert(offsetof(price_level_sell_update_message::fields_type, size) == 17, "unexpected offset of price_level_sell_update_message::fields_type::size");
static_assert(offsetof(price_level_sell_update_message::fields_type, price) == 21, "unexpected offset of price_level_sell_update_message::fields_type::price");
static_assert(sizeof(price_level_sell_update_message::fields_type) == 29, "unexpected sizeof price_level_sell_update_message::fields_type");
static_assert(sizeof(price_level_sell_update_message) == sizeof(message_header) + sizeof(snap_deep::iex_tp_header) + sizeof(snap_deep::iex_tp_message_block_length) + sizeof(snap_deep::iex_tp_message_length) + sizeof(snap_deep::iex_tp_message_type) + 29, "unexpected sizeof price_level_sell_update_message");

#pragma pack(pop)
}
