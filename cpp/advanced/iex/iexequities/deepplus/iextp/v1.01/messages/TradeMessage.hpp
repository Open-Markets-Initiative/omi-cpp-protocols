#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SaleConditionFlags.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/SizeType.hpp"
#include "../types/Price.hpp"
#include "../types/TradeId.hpp"

namespace iex::iexequities::deepplus::iextp::v1_01 {

namespace iextp_deepplus = ::iex::iexequities::deepplus::iextp::v1_01;

#pragma pack(push, 1)

// Trade Message
struct trade_message {

    struct fields_type {
        iextp_deepplus::sale_condition_flags sale_condition_flags;
        iextp_deepplus::timestamp timestamp;
        iextp_deepplus::symbol symbol;
        iextp_deepplus::size_type size;
        iextp_deepplus::price price;
        iextp_deepplus::trade_id trade_id;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::trade_message};

    fields_type fields;

    // parse method
    static trade_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_message*>(buffer);
    }

    // parse method const
    static const trade_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_message::fields_type, sale_condition_flags) == 0, "unexpected offset of trade_message::fields_type::sale_condition_flags");
static_assert(offsetof(trade_message::fields_type, timestamp) == 1, "unexpected offset of trade_message::fields_type::timestamp");
static_assert(offsetof(trade_message::fields_type, symbol) == 9, "unexpected offset of trade_message::fields_type::symbol");
static_assert(offsetof(trade_message::fields_type, size) == 17, "unexpected offset of trade_message::fields_type::size");
static_assert(offsetof(trade_message::fields_type, price) == 21, "unexpected offset of trade_message::fields_type::price");
static_assert(offsetof(trade_message::fields_type, trade_id) == 29, "unexpected offset of trade_message::fields_type::trade_id");
static_assert(sizeof(trade_message::fields_type) == 37, "unexpected sizeof trade_message::fields_type");
static_assert(sizeof(trade_message) == sizeof(message_header) + 37, "unexpected sizeof trade_message");

#pragma pack(pop)
}
