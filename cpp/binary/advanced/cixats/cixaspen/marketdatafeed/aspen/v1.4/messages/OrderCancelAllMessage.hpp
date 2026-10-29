#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OrderId.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

namespace aspen_marketdatafeed = ::cixats::cixaspen::marketdatafeed::aspen::v1_4;

#pragma pack(push, 1)

// Order Cancel All Message
struct order_cancel_all_message {

    struct fields_type {
        aspen_marketdatafeed::timestamp timestamp;
        aspen_marketdatafeed::order_id order_id;
    };

    aspen_marketdatafeed::message_header header = {std::uint16_t(sizeof(aspen_marketdatafeed::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_cancel_all_message};

    fields_type fields;

    // parse method
    static order_cancel_all_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_cancel_all_message*>(buffer);
    }

    // parse method const
    static const order_cancel_all_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_cancel_all_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_cancel_all_message::fields_type, timestamp) == 0, "unexpected offset of order_cancel_all_message::fields_type::timestamp");
static_assert(offsetof(order_cancel_all_message::fields_type, order_id) == 8, "unexpected offset of order_cancel_all_message::fields_type::order_id");
static_assert(sizeof(order_cancel_all_message::fields_type) == 16, "unexpected sizeof order_cancel_all_message::fields_type");
static_assert(sizeof(order_cancel_all_message) == sizeof(aspen_marketdatafeed::message_header) + 16, "unexpected sizeof order_cancel_all_message");

#pragma pack(pop)
}
