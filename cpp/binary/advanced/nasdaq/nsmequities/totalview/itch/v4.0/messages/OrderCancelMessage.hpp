#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/CanceledShares.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v4_0;

#pragma pack(push, 1)

// Order Cancel Message
struct order_cancel_message {

    struct fields_type {
        itch_totalview::nanoseconds nanoseconds;
        itch_totalview::order_reference_number order_reference_number;
        itch_totalview::canceled_shares canceled_shares;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_cancel_message};

    fields_type fields;

    // parse method
    static order_cancel_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_cancel_message*>(buffer);
    }

    // parse method const
    static const order_cancel_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_cancel_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_cancel_message::fields_type, nanoseconds) == 0, "unexpected offset of order_cancel_message::fields_type::nanoseconds");
static_assert(offsetof(order_cancel_message::fields_type, order_reference_number) == 4, "unexpected offset of order_cancel_message::fields_type::order_reference_number");
static_assert(offsetof(order_cancel_message::fields_type, canceled_shares) == 12, "unexpected offset of order_cancel_message::fields_type::canceled_shares");
static_assert(sizeof(order_cancel_message::fields_type) == 16, "unexpected sizeof order_cancel_message::fields_type");
static_assert(sizeof(order_cancel_message) == sizeof(itch_totalview::message_header) + 16, "unexpected sizeof order_cancel_message");

#pragma pack(pop)
}
