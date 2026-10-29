#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OrderId.hpp"
#include "../types/Quantity.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/Side.hpp"
#include "../types/Price.hpp"
#include "../types/Broker.hpp"
#include "../types/ContraBroker.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

namespace aspen_marketdatafeed = ::cixats::cixaspen::marketdatafeed::aspen::v1_4;

#pragma pack(push, 1)

// Order Executed Message
struct order_executed_message {

    struct fields_type {
        aspen_marketdatafeed::timestamp timestamp;
        aspen_marketdatafeed::order_id order_id;
        aspen_marketdatafeed::quantity quantity;
        aspen_marketdatafeed::execution_id execution_id;
        aspen_marketdatafeed::side side;
        aspen_marketdatafeed::price price;
        aspen_marketdatafeed::broker broker;
        aspen_marketdatafeed::contra_broker contra_broker;
    };

    aspen_marketdatafeed::message_header header = {std::uint16_t(sizeof(aspen_marketdatafeed::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_executed_message};

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
static_assert(offsetof(order_executed_message::fields_type, order_id) == 8, "unexpected offset of order_executed_message::fields_type::order_id");
static_assert(offsetof(order_executed_message::fields_type, quantity) == 16, "unexpected offset of order_executed_message::fields_type::quantity");
static_assert(offsetof(order_executed_message::fields_type, execution_id) == 24, "unexpected offset of order_executed_message::fields_type::execution_id");
static_assert(offsetof(order_executed_message::fields_type, side) == 32, "unexpected offset of order_executed_message::fields_type::side");
static_assert(offsetof(order_executed_message::fields_type, price) == 33, "unexpected offset of order_executed_message::fields_type::price");
static_assert(offsetof(order_executed_message::fields_type, broker) == 41, "unexpected offset of order_executed_message::fields_type::broker");
static_assert(offsetof(order_executed_message::fields_type, contra_broker) == 44, "unexpected offset of order_executed_message::fields_type::contra_broker");
static_assert(sizeof(order_executed_message::fields_type) == 47, "unexpected sizeof order_executed_message::fields_type");
static_assert(sizeof(order_executed_message) == sizeof(aspen_marketdatafeed::message_header) + 47, "unexpected sizeof order_executed_message");

#pragma pack(pop)
}
