#pragma once

#include <cstddef>
#include "../structs/SbeHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/OrderId.hpp"
#include "../types/Quantity.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

namespace sbe_memoirdepthfeed = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

#pragma pack(push, 1)

// Order Reduced Message
struct order_reduced_message {

    struct fields_type {
        sbe_memoirdepthfeed::timestamp timestamp;
        sbe_memoirdepthfeed::security_id security_id;
        sbe_memoirdepthfeed::order_id order_id;
        sbe_memoirdepthfeed::quantity quantity;
    };

    sbe_memoirdepthfeed::sbe_header header = {{}, template_id::enum_type::order_reduced_message, schema_id(2), version(259)};

    fields_type fields;

    // parse method
    static order_reduced_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_reduced_message*>(buffer);
    }

    // parse method const
    static const order_reduced_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_reduced_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_reduced_message::fields_type, timestamp) == 0, "unexpected offset of order_reduced_message::fields_type::timestamp");
static_assert(offsetof(order_reduced_message::fields_type, security_id) == 8, "unexpected offset of order_reduced_message::fields_type::security_id");
static_assert(offsetof(order_reduced_message::fields_type, order_id) == 10, "unexpected offset of order_reduced_message::fields_type::order_id");
static_assert(offsetof(order_reduced_message::fields_type, quantity) == 18, "unexpected offset of order_reduced_message::fields_type::quantity");
static_assert(sizeof(order_reduced_message::fields_type) == 22, "unexpected sizeof order_reduced_message::fields_type");
static_assert(sizeof(order_reduced_message) == sizeof(sbe_memoirdepthfeed::sbe_header) + 22, "unexpected sizeof order_reduced_message");

#pragma pack(pop)
}
