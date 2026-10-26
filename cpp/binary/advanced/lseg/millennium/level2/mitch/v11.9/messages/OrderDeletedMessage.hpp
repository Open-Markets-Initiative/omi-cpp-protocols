#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanosecond.hpp"
#include "../types/OrderId.hpp"
#include "../types/OrderDeletedFlags.hpp"
#include "../types/InstrumentId.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

namespace mitch_level2 = ::lseg::millennium::level2::mitch::v11_9;

#pragma pack(push, 1)

// Order Deleted Message
struct order_deleted_message {

    struct fields_type {
        mitch_level2::nanosecond nanosecond;
        mitch_level2::order_id order_id;
        mitch_level2::order_deleted_flags order_deleted_flags;
        mitch_level2::instrument_id instrument_id;
    };

    mitch_level2::message_header header = {std::uint16_t(sizeof(mitch_level2::message_header) + sizeof(fields_type)), message_type::enum_type::order_deleted_message};

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
static_assert(offsetof(order_deleted_message::fields_type, nanosecond) == 0, "unexpected offset of order_deleted_message::fields_type::nanosecond");
static_assert(offsetof(order_deleted_message::fields_type, order_id) == 4, "unexpected offset of order_deleted_message::fields_type::order_id");
static_assert(offsetof(order_deleted_message::fields_type, order_deleted_flags) == 12, "unexpected offset of order_deleted_message::fields_type::order_deleted_flags");
static_assert(offsetof(order_deleted_message::fields_type, instrument_id) == 13, "unexpected offset of order_deleted_message::fields_type::instrument_id");
static_assert(sizeof(order_deleted_message::fields_type) == 17, "unexpected sizeof order_deleted_message::fields_type");
static_assert(sizeof(order_deleted_message) == sizeof(mitch_level2::message_header) + 17, "unexpected sizeof order_deleted_message");

#pragma pack(pop)
}
