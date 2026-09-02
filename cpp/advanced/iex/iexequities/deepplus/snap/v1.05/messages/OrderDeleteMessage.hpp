#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Reserved1.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/OrderIdReference.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

namespace snap_deepplus = ::iex::iexequities::deepplus::snap::v1_05;

#pragma pack(push, 1)

// Order Delete Message
struct order_delete_message {

    struct fields_type {
        snap_deepplus::reserved_1 reserved_1;
        snap_deepplus::timestamp timestamp;
        snap_deepplus::symbol symbol;
        snap_deepplus::order_id_reference order_id_reference;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), {}};

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
static_assert(offsetof(order_delete_message::fields_type, reserved_1) == 0, "unexpected offset of order_delete_message::fields_type::reserved_1");
static_assert(offsetof(order_delete_message::fields_type, timestamp) == 1, "unexpected offset of order_delete_message::fields_type::timestamp");
static_assert(offsetof(order_delete_message::fields_type, symbol) == 9, "unexpected offset of order_delete_message::fields_type::symbol");
static_assert(offsetof(order_delete_message::fields_type, order_id_reference) == 17, "unexpected offset of order_delete_message::fields_type::order_id_reference");
static_assert(sizeof(order_delete_message::fields_type) == 25, "unexpected sizeof order_delete_message::fields_type");
static_assert(sizeof(order_delete_message) == sizeof(message_header) + 25, "unexpected sizeof order_delete_message");

#pragma pack(pop)
}
