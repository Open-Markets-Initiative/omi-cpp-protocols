#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/SymbolId.hpp"
#include "../types/OrderId.hpp"
#include "../types/Side.hpp"
#include "../types/Quantity.hpp"
#include "../types/Symbol.hpp"
#include "../types/Price.hpp"
#include "../types/Broker.hpp"
#include "../types/Reserved1.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

namespace aspen_marketdatafeed = ::cixats::cixaspen::marketdatafeed::aspen::v1_4;

#pragma pack(push, 1)

// New Order Add Message
struct new_order_add_message {

    struct fields_type {
        aspen_marketdatafeed::timestamp timestamp;
        aspen_marketdatafeed::symbol_id symbol_id;
        aspen_marketdatafeed::order_id order_id;
        aspen_marketdatafeed::side side;
        aspen_marketdatafeed::quantity quantity;
        aspen_marketdatafeed::symbol symbol;
        aspen_marketdatafeed::price price;
        aspen_marketdatafeed::broker broker;
        aspen_marketdatafeed::reserved_1 reserved_1;
    };

    aspen_marketdatafeed::message_header header = {std::uint16_t(sizeof(aspen_marketdatafeed::message_header) + sizeof(fields_type) - 2), message_type::enum_type::new_order_add_message};

    fields_type fields;

    // parse method
    static new_order_add_message* parse(std::byte* buffer) {
        return reinterpret_cast<new_order_add_message*>(buffer);
    }

    // parse method const
    static const new_order_add_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const new_order_add_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(new_order_add_message::fields_type, timestamp) == 0, "unexpected offset of new_order_add_message::fields_type::timestamp");
static_assert(offsetof(new_order_add_message::fields_type, symbol_id) == 8, "unexpected offset of new_order_add_message::fields_type::symbol_id");
static_assert(offsetof(new_order_add_message::fields_type, order_id) == 10, "unexpected offset of new_order_add_message::fields_type::order_id");
static_assert(offsetof(new_order_add_message::fields_type, side) == 18, "unexpected offset of new_order_add_message::fields_type::side");
static_assert(offsetof(new_order_add_message::fields_type, quantity) == 19, "unexpected offset of new_order_add_message::fields_type::quantity");
static_assert(offsetof(new_order_add_message::fields_type, symbol) == 27, "unexpected offset of new_order_add_message::fields_type::symbol");
static_assert(offsetof(new_order_add_message::fields_type, price) == 38, "unexpected offset of new_order_add_message::fields_type::price");
static_assert(offsetof(new_order_add_message::fields_type, broker) == 46, "unexpected offset of new_order_add_message::fields_type::broker");
static_assert(offsetof(new_order_add_message::fields_type, reserved_1) == 49, "unexpected offset of new_order_add_message::fields_type::reserved_1");
static_assert(sizeof(new_order_add_message::fields_type) == 50, "unexpected sizeof new_order_add_message::fields_type");
static_assert(sizeof(new_order_add_message) == sizeof(aspen_marketdatafeed::message_header) + 50, "unexpected sizeof new_order_add_message");

#pragma pack(pop)
}
