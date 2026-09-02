#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SaleConditionFlags.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/SizeType.hpp"
#include "../types/Price.hpp"
#include "../types/TradeId.hpp"

namespace iex::iexequities::deep::iextp::v1_06 {

namespace iextp_deep = ::iex::iexequities::deep::iextp::v1_06;

#pragma pack(push, 1)

// Trade Break Message
struct trade_break_message {

    struct fields_type {
        iextp_deep::sale_condition_flags sale_condition_flags;
        iextp_deep::timestamp timestamp;
        iextp_deep::symbol symbol;
        iextp_deep::size_type size;
        iextp_deep::price price;
        iextp_deep::trade_id trade_id;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::trade_break_message};

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
