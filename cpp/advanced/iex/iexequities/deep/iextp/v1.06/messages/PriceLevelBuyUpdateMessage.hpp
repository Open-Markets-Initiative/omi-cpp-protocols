#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/EventFlags.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/SizeType.hpp"
#include "../types/Price.hpp"

namespace iex::iexequities::deep::iextp::v1_06 {

namespace iextp_deep = ::iex::iexequities::deep::iextp::v1_06;

#pragma pack(push, 1)

// Price Level Buy Update Message
struct price_level_buy_update_message {

    struct fields_type {
        iextp_deep::event_flags event_flags;
        iextp_deep::timestamp timestamp;
        iextp_deep::symbol symbol;
        iextp_deep::size_type size;
        iextp_deep::price price;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::price_level_buy_update_message};

    fields_type fields;

    // parse method
    static price_level_buy_update_message* parse(std::byte* buffer) {
        return reinterpret_cast<price_level_buy_update_message*>(buffer);
    }

    // parse method const
    static const price_level_buy_update_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const price_level_buy_update_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(price_level_buy_update_message::fields_type, event_flags) == 0, "unexpected offset of price_level_buy_update_message::fields_type::event_flags");
static_assert(offsetof(price_level_buy_update_message::fields_type, timestamp) == 1, "unexpected offset of price_level_buy_update_message::fields_type::timestamp");
static_assert(offsetof(price_level_buy_update_message::fields_type, symbol) == 9, "unexpected offset of price_level_buy_update_message::fields_type::symbol");
static_assert(offsetof(price_level_buy_update_message::fields_type, size) == 17, "unexpected offset of price_level_buy_update_message::fields_type::size");
static_assert(offsetof(price_level_buy_update_message::fields_type, price) == 21, "unexpected offset of price_level_buy_update_message::fields_type::price");
static_assert(sizeof(price_level_buy_update_message::fields_type) == 29, "unexpected sizeof price_level_buy_update_message::fields_type");
static_assert(sizeof(price_level_buy_update_message) == sizeof(message_header) + 29, "unexpected sizeof price_level_buy_update_message");

#pragma pack(pop)
}
