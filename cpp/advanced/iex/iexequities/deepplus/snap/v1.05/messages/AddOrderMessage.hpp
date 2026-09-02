#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Side.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/OrderId.hpp"
#include "../types/SizeType.hpp"
#include "../types/Price.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

namespace snap_deepplus = ::iex::iexequities::deepplus::snap::v1_05;

#pragma pack(push, 1)

// Add Order Message
struct add_order_message {

    struct fields_type {
        snap_deepplus::side side;
        snap_deepplus::timestamp timestamp;
        snap_deepplus::symbol symbol;
        snap_deepplus::order_id order_id;
        snap_deepplus::size_type size;
        snap_deepplus::price price;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), {}};

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
