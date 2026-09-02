#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SaleConditionFlags.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/OrderIdReference.hpp"
#include "../types/SizeType.hpp"
#include "../types/Price.hpp"
#include "../types/TradeId.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

namespace snap_deepplus = ::iex::iexequities::deepplus::snap::v1_05;

#pragma pack(push, 1)

// Order Executed Message
struct order_executed_message {

    struct fields_type {
        snap_deepplus::sale_condition_flags sale_condition_flags;
        snap_deepplus::timestamp timestamp;
        snap_deepplus::symbol symbol;
        snap_deepplus::order_id_reference order_id_reference;
        snap_deepplus::size_type size;
        snap_deepplus::price price;
        snap_deepplus::trade_id trade_id;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), {}};

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
static_assert(offsetof(order_executed_message::fields_type, sale_condition_flags) == 0, "unexpected offset of order_executed_message::fields_type::sale_condition_flags");
static_assert(offsetof(order_executed_message::fields_type, timestamp) == 1, "unexpected offset of order_executed_message::fields_type::timestamp");
static_assert(offsetof(order_executed_message::fields_type, symbol) == 9, "unexpected offset of order_executed_message::fields_type::symbol");
static_assert(offsetof(order_executed_message::fields_type, order_id_reference) == 17, "unexpected offset of order_executed_message::fields_type::order_id_reference");
static_assert(offsetof(order_executed_message::fields_type, size) == 25, "unexpected offset of order_executed_message::fields_type::size");
static_assert(offsetof(order_executed_message::fields_type, price) == 29, "unexpected offset of order_executed_message::fields_type::price");
static_assert(offsetof(order_executed_message::fields_type, trade_id) == 37, "unexpected offset of order_executed_message::fields_type::trade_id");
static_assert(sizeof(order_executed_message::fields_type) == 45, "unexpected sizeof order_executed_message::fields_type");
static_assert(sizeof(order_executed_message) == sizeof(message_header) + 45, "unexpected sizeof order_executed_message");

#pragma pack(pop)
}
