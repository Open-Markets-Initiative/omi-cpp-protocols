#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SaleConditionFlags.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/SizeType.hpp"
#include "../types/Price.hpp"
#include "../types/TradeId.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

namespace snap_tops = ::iex::iexequities::tops::snap::v1_6;

#pragma pack(push, 1)

// Trade Break Message
struct trade_break_message {

    struct fields_type {
        snap_tops::sale_condition_flags sale_condition_flags;
        snap_tops::timestamp timestamp;
        snap_tops::symbol symbol;
        snap_tops::size_type size;
        snap_tops::price price;
        snap_tops::trade_id trade_id;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), {}};

    fields_type fields;

    // parse method
    static trade_break_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_break_message*>(buffer);
    }

    // parse method const
    static const trade_break_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_break_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_break_message::fields_type, sale_condition_flags) == 0, "unexpected offset of trade_break_message::fields_type::sale_condition_flags");
static_assert(offsetof(trade_break_message::fields_type, timestamp) == 1, "unexpected offset of trade_break_message::fields_type::timestamp");
static_assert(offsetof(trade_break_message::fields_type, symbol) == 9, "unexpected offset of trade_break_message::fields_type::symbol");
static_assert(offsetof(trade_break_message::fields_type, size) == 17, "unexpected offset of trade_break_message::fields_type::size");
static_assert(offsetof(trade_break_message::fields_type, price) == 21, "unexpected offset of trade_break_message::fields_type::price");
static_assert(offsetof(trade_break_message::fields_type, trade_id) == 29, "unexpected offset of trade_break_message::fields_type::trade_id");
static_assert(sizeof(trade_break_message::fields_type) == 37, "unexpected sizeof trade_break_message::fields_type");
static_assert(sizeof(trade_break_message) == sizeof(message_header) + 37, "unexpected sizeof trade_break_message");

#pragma pack(pop)
}
