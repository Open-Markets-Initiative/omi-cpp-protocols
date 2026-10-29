#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/Side.hpp"
#include "../types/Shares.hpp"
#include "../types/Stock.hpp"
#include "../types/Price.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v4_0;

#pragma pack(push, 1)

// Add Order Message
struct add_order_message {

    struct fields_type {
        itch_totalview::nanoseconds nanoseconds;
        itch_totalview::order_reference_number order_reference_number;
        itch_totalview::side side;
        itch_totalview::shares shares;
        itch_totalview::stock stock;
        itch_totalview::price price;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::add_order_message};

    fields_type fields;

    // parse method
    static add_order_message* parse(std::byte* buffer) {
        return reinterpret_cast<add_order_message*>(buffer);
    }

    // parse method const
    static const add_order_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const add_order_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(add_order_message::fields_type, nanoseconds) == 0, "unexpected offset of add_order_message::fields_type::nanoseconds");
static_assert(offsetof(add_order_message::fields_type, order_reference_number) == 4, "unexpected offset of add_order_message::fields_type::order_reference_number");
static_assert(offsetof(add_order_message::fields_type, side) == 12, "unexpected offset of add_order_message::fields_type::side");
static_assert(offsetof(add_order_message::fields_type, shares) == 13, "unexpected offset of add_order_message::fields_type::shares");
static_assert(offsetof(add_order_message::fields_type, stock) == 17, "unexpected offset of add_order_message::fields_type::stock");
static_assert(offsetof(add_order_message::fields_type, price) == 23, "unexpected offset of add_order_message::fields_type::price");
static_assert(sizeof(add_order_message::fields_type) == 27, "unexpected sizeof add_order_message::fields_type");
static_assert(sizeof(add_order_message) == sizeof(itch_totalview::message_header) + 27, "unexpected sizeof add_order_message");

#pragma pack(pop)
}
