#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanosecond.hpp"
#include "../types/OrderId.hpp"
#include "../types/NewQuantity.hpp"
#include "../types/NewPrice.hpp"
#include "../types/OrderModifiedFlags.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

namespace mitch_level2 = ::lseg::millennium::level2::mitch::v11_9;

#pragma pack(push, 1)

// Order Modified Message
struct order_modified_message {

    struct fields_type {
        mitch_level2::nanosecond nanosecond;
        mitch_level2::order_id order_id;
        mitch_level2::new_quantity new_quantity;
        mitch_level2::new_price new_price;
        mitch_level2::order_modified_flags order_modified_flags;
    };

    mitch_level2::message_header header = {std::uint16_t(sizeof(mitch_level2::message_header) + sizeof(fields_type)), message_type::enum_type::order_modified_message};

    fields_type fields;

    // parse method
    static order_modified_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_modified_message*>(buffer);
    }

    // parse method const
    static const order_modified_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_modified_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_modified_message::fields_type, nanosecond) == 0, "unexpected offset of order_modified_message::fields_type::nanosecond");
static_assert(offsetof(order_modified_message::fields_type, order_id) == 4, "unexpected offset of order_modified_message::fields_type::order_id");
static_assert(offsetof(order_modified_message::fields_type, new_quantity) == 12, "unexpected offset of order_modified_message::fields_type::new_quantity");
static_assert(offsetof(order_modified_message::fields_type, new_price) == 16, "unexpected offset of order_modified_message::fields_type::new_price");
static_assert(offsetof(order_modified_message::fields_type, order_modified_flags) == 24, "unexpected offset of order_modified_message::fields_type::order_modified_flags");
static_assert(sizeof(order_modified_message::fields_type) == 25, "unexpected sizeof order_modified_message::fields_type");
static_assert(sizeof(order_modified_message) == sizeof(mitch_level2::message_header) + 25, "unexpected sizeof order_modified_message");

#pragma pack(pop)
}
