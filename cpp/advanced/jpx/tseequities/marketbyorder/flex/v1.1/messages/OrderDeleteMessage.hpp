#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeMicroseconds.hpp"
#include "../types/OrderId.hpp"
#include "../types/Side.hpp"
#include "../types/ModificationFlag.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

namespace flex_marketbyorder = ::jpx::tseequities::marketbyorder::flex::v1_1;

#pragma pack(push, 1)

// Order Delete Message
struct order_delete_message {

    struct fields_type {
        flex_marketbyorder::time_microseconds time_microseconds;
        flex_marketbyorder::order_id order_id;
        flex_marketbyorder::side side;
        flex_marketbyorder::modification_flag modification_flag;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 1), message_type::enum_type::order_delete_message};

    fields_type fields;

    // parse method
    static order_delete_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_delete_message*>(buffer);
    }

    // parse method const
    static const order_delete_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_delete_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_delete_message::fields_type, time_microseconds) == 0, "unexpected offset of order_delete_message::fields_type::time_microseconds");
static_assert(offsetof(order_delete_message::fields_type, order_id) == 4, "unexpected offset of order_delete_message::fields_type::order_id");
static_assert(offsetof(order_delete_message::fields_type, side) == 8, "unexpected offset of order_delete_message::fields_type::side");
static_assert(offsetof(order_delete_message::fields_type, modification_flag) == 9, "unexpected offset of order_delete_message::fields_type::modification_flag");
static_assert(sizeof(order_delete_message::fields_type) == 10, "unexpected sizeof order_delete_message::fields_type");
static_assert(sizeof(order_delete_message) == sizeof(message_header) + 10, "unexpected sizeof order_delete_message");

#pragma pack(pop)
}
