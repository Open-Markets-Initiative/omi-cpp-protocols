#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OriginalOrderReferenceNumber.hpp"
#include "../types/NewOrderReferenceNumber.hpp"
#include "../types/Shares.hpp"
#include "../types/Price.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v4_0;

#pragma pack(push, 1)

// Order Replace Message
struct order_replace_message {

    struct fields_type {
        itch_totalview::nanoseconds nanoseconds;
        itch_totalview::original_order_reference_number original_order_reference_number;
        itch_totalview::new_order_reference_number new_order_reference_number;
        itch_totalview::shares shares;
        itch_totalview::price price;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_replace_message};

    fields_type fields;

    // parse method
    static order_replace_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_replace_message*>(buffer);
    }

    // parse method const
    static const order_replace_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_replace_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_replace_message::fields_type, nanoseconds) == 0, "unexpected offset of order_replace_message::fields_type::nanoseconds");
static_assert(offsetof(order_replace_message::fields_type, original_order_reference_number) == 4, "unexpected offset of order_replace_message::fields_type::original_order_reference_number");
static_assert(offsetof(order_replace_message::fields_type, new_order_reference_number) == 12, "unexpected offset of order_replace_message::fields_type::new_order_reference_number");
static_assert(offsetof(order_replace_message::fields_type, shares) == 20, "unexpected offset of order_replace_message::fields_type::shares");
static_assert(offsetof(order_replace_message::fields_type, price) == 24, "unexpected offset of order_replace_message::fields_type::price");
static_assert(sizeof(order_replace_message::fields_type) == 28, "unexpected sizeof order_replace_message::fields_type");
static_assert(sizeof(order_replace_message) == sizeof(itch_totalview::message_header) + 28, "unexpected sizeof order_replace_message");

#pragma pack(pop)
}
