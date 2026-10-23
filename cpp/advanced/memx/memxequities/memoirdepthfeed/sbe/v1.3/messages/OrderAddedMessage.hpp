#pragma once

#include <cstddef>
#include "../structs/SbeHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/OrderId.hpp"
#include "../types/Side.hpp"
#include "../types/Quantity.hpp"
#include "../types/Price.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

namespace sbe_memoirdepthfeed = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

#pragma pack(push, 1)

// Order Added Message
struct order_added_message {

    struct fields_type {
        sbe_memoirdepthfeed::timestamp timestamp;
        sbe_memoirdepthfeed::security_id security_id;
        sbe_memoirdepthfeed::order_id order_id;
        sbe_memoirdepthfeed::side side;
        sbe_memoirdepthfeed::quantity quantity;
        sbe_memoirdepthfeed::price price;
    };

    sbe_memoirdepthfeed::sbe_header header = {{}, template_id::enum_type::order_added_message, schema_id(2), version(259)};

    fields_type fields;

    // parse method
    static order_added_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_added_message*>(buffer);
    }

    // parse method const
    static const order_added_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_added_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_added_message::fields_type, timestamp) == 0, "unexpected offset of order_added_message::fields_type::timestamp");
static_assert(offsetof(order_added_message::fields_type, security_id) == 8, "unexpected offset of order_added_message::fields_type::security_id");
static_assert(offsetof(order_added_message::fields_type, order_id) == 10, "unexpected offset of order_added_message::fields_type::order_id");
static_assert(offsetof(order_added_message::fields_type, side) == 18, "unexpected offset of order_added_message::fields_type::side");
static_assert(offsetof(order_added_message::fields_type, quantity) == 19, "unexpected offset of order_added_message::fields_type::quantity");
static_assert(offsetof(order_added_message::fields_type, price) == 23, "unexpected offset of order_added_message::fields_type::price");
static_assert(sizeof(order_added_message::fields_type) == 31, "unexpected sizeof order_added_message::fields_type");
static_assert(sizeof(order_added_message) == sizeof(sbe_memoirdepthfeed::sbe_header) + 31, "unexpected sizeof order_added_message");

#pragma pack(pop)
}
