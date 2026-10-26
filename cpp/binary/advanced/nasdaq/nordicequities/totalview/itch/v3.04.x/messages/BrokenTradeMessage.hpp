#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/MatchNumber.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

namespace itch_totalview = ::nasdaq::nordicequities::totalview::itch::v3_04_x;

#pragma pack(push, 1)

// Broken Trade Message
struct broken_trade_message {

    struct fields_type {
        itch_totalview::timestamp timestamp;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::match_number match_number;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::broken_trade_message};

    fields_type fields;

    // parse method
    static broken_trade_message* parse(std::byte* buffer) {
        return reinterpret_cast<broken_trade_message*>(buffer);
    }

    // parse method const
    static const broken_trade_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const broken_trade_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(broken_trade_message::fields_type, timestamp) == 0, "unexpected offset of broken_trade_message::fields_type::timestamp");
static_assert(offsetof(broken_trade_message::fields_type, tracking_number) == 8, "unexpected offset of broken_trade_message::fields_type::tracking_number");
static_assert(offsetof(broken_trade_message::fields_type, match_number) == 10, "unexpected offset of broken_trade_message::fields_type::match_number");
static_assert(sizeof(broken_trade_message::fields_type) == 14, "unexpected sizeof broken_trade_message::fields_type");
static_assert(sizeof(broken_trade_message) == sizeof(itch_totalview::message_header) + 14, "unexpected sizeof broken_trade_message");

#pragma pack(pop)
}
