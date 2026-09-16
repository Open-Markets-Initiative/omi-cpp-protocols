#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/MatchNumber.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

#pragma pack(push, 1)

// Broken Trade Message
struct broken_trade_message {

    struct fields_type {
        itch_totalview::stock_locate stock_locate;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::timestamp timestamp;
        itch_totalview::match_number match_number;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::broken_trade_message};

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
static_assert(offsetof(broken_trade_message::fields_type, stock_locate) == 0, "unexpected offset of broken_trade_message::fields_type::stock_locate");
static_assert(offsetof(broken_trade_message::fields_type, tracking_number) == 2, "unexpected offset of broken_trade_message::fields_type::tracking_number");
static_assert(offsetof(broken_trade_message::fields_type, timestamp) == 4, "unexpected offset of broken_trade_message::fields_type::timestamp");
static_assert(offsetof(broken_trade_message::fields_type, match_number) == 10, "unexpected offset of broken_trade_message::fields_type::match_number");
static_assert(sizeof(broken_trade_message::fields_type) == 18, "unexpected sizeof broken_trade_message::fields_type");
static_assert(sizeof(broken_trade_message) == sizeof(message_header) + 18, "unexpected sizeof broken_trade_message");

#pragma pack(pop)
}
