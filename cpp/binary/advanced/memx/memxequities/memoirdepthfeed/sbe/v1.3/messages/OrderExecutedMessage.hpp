#pragma once

#include <cstddef>
#include "../structs/SbeHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/OrderId.hpp"
#include "../types/TradeId.hpp"
#include "../types/Quantity.hpp"
#include "../types/Price.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

namespace sbe_memoirdepthfeed = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

#pragma pack(push, 1)

// Order Executed Message
struct order_executed_message {

    struct fields_type {
        sbe_memoirdepthfeed::timestamp timestamp;
        sbe_memoirdepthfeed::security_id security_id;
        sbe_memoirdepthfeed::order_id order_id;
        sbe_memoirdepthfeed::trade_id trade_id;
        sbe_memoirdepthfeed::quantity quantity;
        sbe_memoirdepthfeed::price price;
    };

    sbe_memoirdepthfeed::sbe_header header = {{}, template_id::enum_type::order_executed_message, schema_id(2), version(259)};

    fields_type fields;

    // parse method
    static order_executed_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_executed_message*>(buffer);
    }

    // parse method const
    static const order_executed_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_executed_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_executed_message::fields_type, timestamp) == 0, "unexpected offset of order_executed_message::fields_type::timestamp");
static_assert(offsetof(order_executed_message::fields_type, security_id) == 8, "unexpected offset of order_executed_message::fields_type::security_id");
static_assert(offsetof(order_executed_message::fields_type, order_id) == 10, "unexpected offset of order_executed_message::fields_type::order_id");
static_assert(offsetof(order_executed_message::fields_type, trade_id) == 18, "unexpected offset of order_executed_message::fields_type::trade_id");
static_assert(offsetof(order_executed_message::fields_type, quantity) == 26, "unexpected offset of order_executed_message::fields_type::quantity");
static_assert(offsetof(order_executed_message::fields_type, price) == 30, "unexpected offset of order_executed_message::fields_type::price");
static_assert(sizeof(order_executed_message::fields_type) == 38, "unexpected sizeof order_executed_message::fields_type");
static_assert(sizeof(order_executed_message) == sizeof(sbe_memoirdepthfeed::sbe_header) + 38, "unexpected sizeof order_executed_message");

#pragma pack(pop)
}
