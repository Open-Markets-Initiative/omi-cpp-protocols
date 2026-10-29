#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OrderNumber.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

namespace itch_pts = ::jnx::jnxequities::pts::itch::v1_7;

#pragma pack(push, 1)

// Order Deleted Message
struct order_deleted_message {

    struct fields_type {
        itch_pts::nanoseconds nanoseconds;
        itch_pts::order_number order_number;
    };

    itch_pts::message_header header = {std::uint16_t(sizeof(itch_pts::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_deleted_message};

    fields_type fields;

    // parse method
    static order_deleted_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_deleted_message*>(buffer);
    }

    // parse method const
    static const order_deleted_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_deleted_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_deleted_message::fields_type, nanoseconds) == 0, "unexpected offset of order_deleted_message::fields_type::nanoseconds");
static_assert(offsetof(order_deleted_message::fields_type, order_number) == 4, "unexpected offset of order_deleted_message::fields_type::order_number");
static_assert(sizeof(order_deleted_message::fields_type) == 12, "unexpected sizeof order_deleted_message::fields_type");
static_assert(sizeof(order_deleted_message) == sizeof(itch_pts::message_header) + 12, "unexpected sizeof order_deleted_message");

#pragma pack(pop)
}
