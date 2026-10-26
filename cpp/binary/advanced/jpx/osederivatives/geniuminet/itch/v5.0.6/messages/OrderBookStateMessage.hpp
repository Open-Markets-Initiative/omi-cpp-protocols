#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OrderBookId.hpp"
#include "../types/StateName.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

namespace itch_geniuminet = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

#pragma pack(push, 1)

// Order Book State Message
struct order_book_state_message {

    struct fields_type {
        itch_geniuminet::nanoseconds nanoseconds;
        itch_geniuminet::order_book_id order_book_id;
        itch_geniuminet::state_name state_name;
    };

    itch_geniuminet::message_header header = {std::uint16_t(sizeof(itch_geniuminet::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_book_state_message};

    fields_type fields;

    // parse method
    static order_book_state_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_book_state_message*>(buffer);
    }

    // parse method const
    static const order_book_state_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_book_state_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_book_state_message::fields_type, nanoseconds) == 0, "unexpected offset of order_book_state_message::fields_type::nanoseconds");
static_assert(offsetof(order_book_state_message::fields_type, order_book_id) == 4, "unexpected offset of order_book_state_message::fields_type::order_book_id");
static_assert(offsetof(order_book_state_message::fields_type, state_name) == 8, "unexpected offset of order_book_state_message::fields_type::state_name");
static_assert(sizeof(order_book_state_message::fields_type) == 28, "unexpected sizeof order_book_state_message::fields_type");
static_assert(sizeof(order_book_state_message) == sizeof(itch_geniuminet::message_header) + 28, "unexpected sizeof order_book_state_message");

#pragma pack(pop)
}
