#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OptionId.hpp"
#include "../types/CurrentTradingState.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

namespace itch_topofmarket = ::nasdaq::phlxoptions::topofmarket::itch::v3_4;

#pragma pack(push, 1)

// Trading Action Message
struct trading_action_message {

    struct fields_type {
        itch_topofmarket::nanoseconds nanoseconds;
        itch_topofmarket::option_id option_id;
        itch_topofmarket::current_trading_state current_trading_state;
    };

    itch_topofmarket::message_header header = {std::uint16_t(sizeof(itch_topofmarket::message_header) + sizeof(fields_type) - 2), message_type::enum_type::trading_action_message};

    fields_type fields;

    // parse method
    static trading_action_message* parse(std::byte* buffer) {
        return reinterpret_cast<trading_action_message*>(buffer);
    }

    // parse method const
    static const trading_action_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trading_action_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trading_action_message::fields_type, nanoseconds) == 0, "unexpected offset of trading_action_message::fields_type::nanoseconds");
static_assert(offsetof(trading_action_message::fields_type, option_id) == 4, "unexpected offset of trading_action_message::fields_type::option_id");
static_assert(offsetof(trading_action_message::fields_type, current_trading_state) == 8, "unexpected offset of trading_action_message::fields_type::current_trading_state");
static_assert(sizeof(trading_action_message::fields_type) == 9, "unexpected sizeof trading_action_message::fields_type");
static_assert(sizeof(trading_action_message) == sizeof(itch_topofmarket::message_header) + 9, "unexpected sizeof trading_action_message");

#pragma pack(pop)
}
