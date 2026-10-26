#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OptionId.hpp"
#include "../types/CurrentTradingState.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

#pragma pack(push, 1)

// Trading Action Message
struct trading_action_message {

    struct fields_type {
        itch_itto::tracking_number tracking_number;
        itch_itto::timestamp timestamp;
        itch_itto::option_id option_id;
        itch_itto::current_trading_state current_trading_state;
    };

    itch_itto::message_header header = {std::uint16_t(sizeof(itch_itto::message_header) + sizeof(fields_type) - 2), message_type::enum_type::trading_action_message};

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
static_assert(offsetof(trading_action_message::fields_type, tracking_number) == 0, "unexpected offset of trading_action_message::fields_type::tracking_number");
static_assert(offsetof(trading_action_message::fields_type, timestamp) == 2, "unexpected offset of trading_action_message::fields_type::timestamp");
static_assert(offsetof(trading_action_message::fields_type, option_id) == 8, "unexpected offset of trading_action_message::fields_type::option_id");
static_assert(offsetof(trading_action_message::fields_type, current_trading_state) == 12, "unexpected offset of trading_action_message::fields_type::current_trading_state");
static_assert(sizeof(trading_action_message::fields_type) == 13, "unexpected sizeof trading_action_message::fields_type");
static_assert(sizeof(trading_action_message) == sizeof(itch_itto::message_header) + 13, "unexpected sizeof trading_action_message");

#pragma pack(pop)
}
