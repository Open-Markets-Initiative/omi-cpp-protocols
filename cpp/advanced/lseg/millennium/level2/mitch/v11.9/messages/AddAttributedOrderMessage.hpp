#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanosecond.hpp"
#include "../types/OrderId.hpp"
#include "../types/Side.hpp"
#include "../types/Quantity.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/ReservedA.hpp"
#include "../types/ReservedB.hpp"
#include "../types/Price.hpp"
#include "../types/Attribution.hpp"
#include "../types/AddAttributedOrderFlags.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

namespace mitch_level2 = ::lseg::millennium::level2::mitch::v11_9;

#pragma pack(push, 1)

// Add Attributed Order Message
struct add_attributed_order_message {

    struct fields_type {
        mitch_level2::nanosecond nanosecond;
        mitch_level2::order_id order_id;
        mitch_level2::side side;
        mitch_level2::quantity quantity;
        mitch_level2::instrument_id instrument_id;
        mitch_level2::reserved_a reserved_a;
        mitch_level2::reserved_b reserved_b;
        mitch_level2::price price;
        mitch_level2::attribution attribution;
        mitch_level2::add_attributed_order_flags add_attributed_order_flags;
    };

    mitch_level2::message_header header = {std::uint16_t(sizeof(mitch_level2::message_header) + sizeof(fields_type)), message_type::enum_type::add_attributed_order_message};

    fields_type fields;

    // parse method
    static add_attributed_order_message* parse(std::byte* buffer) {
        return reinterpret_cast<add_attributed_order_message*>(buffer);
    }

    // parse method const
    static const add_attributed_order_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const add_attributed_order_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(add_attributed_order_message::fields_type, nanosecond) == 0, "unexpected offset of add_attributed_order_message::fields_type::nanosecond");
static_assert(offsetof(add_attributed_order_message::fields_type, order_id) == 4, "unexpected offset of add_attributed_order_message::fields_type::order_id");
static_assert(offsetof(add_attributed_order_message::fields_type, side) == 12, "unexpected offset of add_attributed_order_message::fields_type::side");
static_assert(offsetof(add_attributed_order_message::fields_type, quantity) == 13, "unexpected offset of add_attributed_order_message::fields_type::quantity");
static_assert(offsetof(add_attributed_order_message::fields_type, instrument_id) == 17, "unexpected offset of add_attributed_order_message::fields_type::instrument_id");
static_assert(offsetof(add_attributed_order_message::fields_type, reserved_a) == 21, "unexpected offset of add_attributed_order_message::fields_type::reserved_a");
static_assert(offsetof(add_attributed_order_message::fields_type, reserved_b) == 22, "unexpected offset of add_attributed_order_message::fields_type::reserved_b");
static_assert(offsetof(add_attributed_order_message::fields_type, price) == 23, "unexpected offset of add_attributed_order_message::fields_type::price");
static_assert(offsetof(add_attributed_order_message::fields_type, attribution) == 31, "unexpected offset of add_attributed_order_message::fields_type::attribution");
static_assert(offsetof(add_attributed_order_message::fields_type, add_attributed_order_flags) == 42, "unexpected offset of add_attributed_order_message::fields_type::add_attributed_order_flags");
static_assert(sizeof(add_attributed_order_message::fields_type) == 43, "unexpected sizeof add_attributed_order_message::fields_type");
static_assert(sizeof(add_attributed_order_message) == sizeof(mitch_level2::message_header) + 43, "unexpected sizeof add_attributed_order_message");

#pragma pack(pop)
}
