#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/MatchNumber.hpp"
#include "../types/Mpid.hpp"
#include "../types/MpidCounterparty.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

namespace itch_totalview = ::nasdaq::nordicequities::totalview::itch::v3_04_x;

#pragma pack(push, 1)

// Order Executed Message
struct order_executed_message {

    struct fields_type {
        itch_totalview::timestamp timestamp;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::order_reference_number order_reference_number;
        itch_totalview::executed_quantity executed_quantity;
        itch_totalview::match_number match_number;
        itch_totalview::mpid mpid;
        itch_totalview::mpid_counterparty mpid_counterparty;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_executed_message};

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
static_assert(offsetof(order_executed_message::fields_type, tracking_number) == 8, "unexpected offset of order_executed_message::fields_type::tracking_number");
static_assert(offsetof(order_executed_message::fields_type, order_reference_number) == 10, "unexpected offset of order_executed_message::fields_type::order_reference_number");
static_assert(offsetof(order_executed_message::fields_type, executed_quantity) == 18, "unexpected offset of order_executed_message::fields_type::executed_quantity");
static_assert(offsetof(order_executed_message::fields_type, match_number) == 22, "unexpected offset of order_executed_message::fields_type::match_number");
static_assert(offsetof(order_executed_message::fields_type, mpid) == 26, "unexpected offset of order_executed_message::fields_type::mpid");
static_assert(offsetof(order_executed_message::fields_type, mpid_counterparty) == 30, "unexpected offset of order_executed_message::fields_type::mpid_counterparty");
static_assert(sizeof(order_executed_message::fields_type) == 34, "unexpected sizeof order_executed_message::fields_type");
static_assert(sizeof(order_executed_message) == sizeof(itch_totalview::message_header) + 34, "unexpected sizeof order_executed_message");

#pragma pack(pop)
}
