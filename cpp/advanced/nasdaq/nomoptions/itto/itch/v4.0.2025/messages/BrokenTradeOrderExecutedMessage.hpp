#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/CrossNumber.hpp"
#include "../types/MatchNumber.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

#pragma pack(push, 1)

// Broken Trade Order Executed Message
struct broken_trade_order_executed_message {

    struct fields_type {
        itch_itto::tracking_number tracking_number;
        itch_itto::timestamp timestamp;
        itch_itto::cross_number cross_number;
        itch_itto::match_number match_number;
    };

    itch_itto::message_header header = {std::uint16_t(sizeof(itch_itto::message_header) + sizeof(fields_type) - 2), message_type::enum_type::broken_trade_order_executed_message};

    fields_type fields;

    // parse method
    static broken_trade_order_executed_message* parse(std::byte* buffer) {
        return reinterpret_cast<broken_trade_order_executed_message*>(buffer);
    }

    // parse method const
    static const broken_trade_order_executed_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const broken_trade_order_executed_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(broken_trade_order_executed_message::fields_type, tracking_number) == 0, "unexpected offset of broken_trade_order_executed_message::fields_type::tracking_number");
static_assert(offsetof(broken_trade_order_executed_message::fields_type, timestamp) == 2, "unexpected offset of broken_trade_order_executed_message::fields_type::timestamp");
static_assert(offsetof(broken_trade_order_executed_message::fields_type, cross_number) == 8, "unexpected offset of broken_trade_order_executed_message::fields_type::cross_number");
static_assert(offsetof(broken_trade_order_executed_message::fields_type, match_number) == 12, "unexpected offset of broken_trade_order_executed_message::fields_type::match_number");
static_assert(sizeof(broken_trade_order_executed_message::fields_type) == 16, "unexpected sizeof broken_trade_order_executed_message::fields_type");
static_assert(sizeof(broken_trade_order_executed_message) == sizeof(itch_itto::message_header) + 16, "unexpected sizeof broken_trade_order_executed_message");

#pragma pack(pop)
}
