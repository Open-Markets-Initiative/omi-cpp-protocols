#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanosecond.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/ReservedA.hpp"
#include "../types/ReservedB.hpp"
#include "../types/OrderBookClearFlags.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

namespace mitch_level2 = ::lseg::millennium::level2::mitch::v11_9;

#pragma pack(push, 1)

// Order Book Clear Message
struct order_book_clear_message {

    struct fields_type {
        mitch_level2::nanosecond nanosecond;
        mitch_level2::instrument_id instrument_id;
        mitch_level2::reserved_a reserved_a;
        mitch_level2::reserved_b reserved_b;
        mitch_level2::order_book_clear_flags order_book_clear_flags;
    };

    mitch_level2::message_header header = {std::uint16_t(sizeof(mitch_level2::message_header) + sizeof(fields_type)), message_type::enum_type::order_book_clear_message};

    fields_type fields;

    // parse method
    static order_book_clear_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_book_clear_message*>(buffer);
    }

    // parse method const
    static const order_book_clear_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_book_clear_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_book_clear_message::fields_type, nanosecond) == 0, "unexpected offset of order_book_clear_message::fields_type::nanosecond");
static_assert(offsetof(order_book_clear_message::fields_type, instrument_id) == 4, "unexpected offset of order_book_clear_message::fields_type::instrument_id");
static_assert(offsetof(order_book_clear_message::fields_type, reserved_a) == 8, "unexpected offset of order_book_clear_message::fields_type::reserved_a");
static_assert(offsetof(order_book_clear_message::fields_type, reserved_b) == 9, "unexpected offset of order_book_clear_message::fields_type::reserved_b");
static_assert(offsetof(order_book_clear_message::fields_type, order_book_clear_flags) == 10, "unexpected offset of order_book_clear_message::fields_type::order_book_clear_flags");
static_assert(sizeof(order_book_clear_message::fields_type) == 11, "unexpected sizeof order_book_clear_message::fields_type");
static_assert(sizeof(order_book_clear_message) == sizeof(mitch_level2::message_header) + 11, "unexpected sizeof order_book_clear_message");

#pragma pack(pop)
}
