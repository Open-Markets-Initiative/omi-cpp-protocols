#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Side.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/OrderId.hpp"
#include "../types/SizeType.hpp"
#include "../types/Price.hpp"

namespace iex::iexequities::deepplus::iextp::v1_04 {

namespace iextp_deepplus = ::iex::iexequities::deepplus::iextp::v1_04;

#pragma pack(push, 1)

// Add Order Message
struct add_order_message {

    struct fields_type {
        iextp_deepplus::side side;
        iextp_deepplus::timestamp timestamp;
        iextp_deepplus::symbol symbol;
        iextp_deepplus::order_id order_id;
        iextp_deepplus::size_type size;
        iextp_deepplus::price price;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::add_order_message};

    fields_type fields;

    // parse method
    static add_order_message* parse(std::byte* buffer) {
        return reinterpret_cast<add_order_message*>(buffer);
    }

    // parse method const
    static const add_order_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const add_order_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(add_order_message::fields_type, side) == 0, "unexpected offset of add_order_message::fields_type::side");
static_assert(offsetof(add_order_message::fields_type, timestamp) == 1, "unexpected offset of add_order_message::fields_type::timestamp");
static_assert(offsetof(add_order_message::fields_type, symbol) == 9, "unexpected offset of add_order_message::fields_type::symbol");
static_assert(offsetof(add_order_message::fields_type, order_id) == 17, "unexpected offset of add_order_message::fields_type::order_id");
static_assert(offsetof(add_order_message::fields_type, size) == 25, "unexpected offset of add_order_message::fields_type::size");
static_assert(offsetof(add_order_message::fields_type, price) == 29, "unexpected offset of add_order_message::fields_type::price");
static_assert(sizeof(add_order_message::fields_type) == 37, "unexpected sizeof add_order_message::fields_type");
static_assert(sizeof(add_order_message) == sizeof(message_header) + 37, "unexpected sizeof add_order_message");

#pragma pack(pop)
}
