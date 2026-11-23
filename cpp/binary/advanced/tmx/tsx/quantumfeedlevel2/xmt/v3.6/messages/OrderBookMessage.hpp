// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/OrderBookMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/BusinessHeader.hpp"
#include "../types/Symbol.hpp"
#include "../types/BrokerNumber.hpp"
#include "../types/OrderSide.hpp"
#include "../types/OrderId.hpp"
#include "../types/OrderPrice.hpp"
#include "../types/Volume.hpp"
#include "../types/PriorityTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

#pragma pack(push, 1)

// Order Book Message
struct order_book_message {

    struct fields_type {
        xmt_quantumfeedlevel2::symbol symbol;
        xmt_quantumfeedlevel2::broker_number broker_number;
        xmt_quantumfeedlevel2::order_side order_side;
        xmt_quantumfeedlevel2::order_id order_id;
        xmt_quantumfeedlevel2::order_price order_price;
        xmt_quantumfeedlevel2::volume volume;
        xmt_quantumfeedlevel2::priority_time_stamp priority_time_stamp;
    };

    xmt_quantumfeedlevel2::business_header header = {{}, {}, {}, sequence_0(0), {}};

    fields_type fields;

    // parse method
    static order_book_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_book_message*>(buffer);
    }

    // parse method const
    static const order_book_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_book_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_book_message::fields_type, symbol) == 0, "unexpected offset of order_book_message::fields_type::symbol");
static_assert(offsetof(order_book_message::fields_type, broker_number) == 12, "unexpected offset of order_book_message::fields_type::broker_number");
static_assert(offsetof(order_book_message::fields_type, order_side) == 14, "unexpected offset of order_book_message::fields_type::order_side");
static_assert(offsetof(order_book_message::fields_type, order_id) == 15, "unexpected offset of order_book_message::fields_type::order_id");
static_assert(offsetof(order_book_message::fields_type, order_price) == 23, "unexpected offset of order_book_message::fields_type::order_price");
static_assert(offsetof(order_book_message::fields_type, volume) == 31, "unexpected offset of order_book_message::fields_type::volume");
static_assert(offsetof(order_book_message::fields_type, priority_time_stamp) == 35, "unexpected offset of order_book_message::fields_type::priority_time_stamp");
static_assert(sizeof(order_book_message::fields_type) == 43, "unexpected sizeof order_book_message::fields_type");
static_assert(sizeof(order_book_message) == sizeof(xmt_quantumfeedlevel2::business_header) + 43, "unexpected sizeof order_book_message");

#pragma pack(pop)
}
