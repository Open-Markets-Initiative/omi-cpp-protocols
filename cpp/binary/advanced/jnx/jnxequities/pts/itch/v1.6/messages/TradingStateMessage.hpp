#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OrderbookId.hpp"
#include "../types/Group.hpp"
#include "../types/TradingState.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

namespace itch_pts = ::jnx::jnxequities::pts::itch::v1_6;

#pragma pack(push, 1)

// Trading State Message
struct trading_state_message {

    struct fields_type {
        itch_pts::nanoseconds nanoseconds;
        itch_pts::orderbook_id orderbook_id;
        itch_pts::group group;
        itch_pts::trading_state trading_state;
    };

    itch_pts::message_header header = {std::uint16_t(sizeof(itch_pts::message_header) + sizeof(fields_type) - 2), message_type::enum_type::trading_state_message};

    fields_type fields;

    // parse method
    static trading_state_message* parse(std::byte* buffer) {
        return reinterpret_cast<trading_state_message*>(buffer);
    }

    // parse method const
    static const trading_state_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trading_state_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trading_state_message::fields_type, nanoseconds) == 0, "unexpected offset of trading_state_message::fields_type::nanoseconds");
static_assert(offsetof(trading_state_message::fields_type, orderbook_id) == 4, "unexpected offset of trading_state_message::fields_type::orderbook_id");
static_assert(offsetof(trading_state_message::fields_type, group) == 8, "unexpected offset of trading_state_message::fields_type::group");
static_assert(offsetof(trading_state_message::fields_type, trading_state) == 12, "unexpected offset of trading_state_message::fields_type::trading_state");
static_assert(sizeof(trading_state_message::fields_type) == 13, "unexpected sizeof trading_state_message::fields_type");
static_assert(sizeof(trading_state_message) == sizeof(itch_pts::message_header) + 13, "unexpected sizeof trading_state_message");

#pragma pack(pop)
}
