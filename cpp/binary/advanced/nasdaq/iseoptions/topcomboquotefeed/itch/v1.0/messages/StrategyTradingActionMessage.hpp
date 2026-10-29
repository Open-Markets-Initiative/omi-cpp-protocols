#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/StrategyId.hpp"
#include "../types/CurrentTradingState.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

namespace itch_topcomboquotefeed = ::nasdaq::iseoptions::topcomboquotefeed::itch::v1_0;

#pragma pack(push, 1)

// Strategy Trading Action Message
struct strategy_trading_action_message {

    struct fields_type {
        itch_topcomboquotefeed::timestamp timestamp;
        itch_topcomboquotefeed::strategy_id strategy_id;
        itch_topcomboquotefeed::current_trading_state current_trading_state;
    };

    itch_topcomboquotefeed::message_header header = {std::uint16_t(sizeof(itch_topcomboquotefeed::message_header) + sizeof(fields_type) - 2), message_type::enum_type::strategy_trading_action_message};

    fields_type fields;

    // parse method
    static strategy_trading_action_message* parse(std::byte* buffer) {
        return reinterpret_cast<strategy_trading_action_message*>(buffer);
    }

    // parse method const
    static const strategy_trading_action_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const strategy_trading_action_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(strategy_trading_action_message::fields_type, timestamp) == 0, "unexpected offset of strategy_trading_action_message::fields_type::timestamp");
static_assert(offsetof(strategy_trading_action_message::fields_type, strategy_id) == 6, "unexpected offset of strategy_trading_action_message::fields_type::strategy_id");
static_assert(offsetof(strategy_trading_action_message::fields_type, current_trading_state) == 10, "unexpected offset of strategy_trading_action_message::fields_type::current_trading_state");
static_assert(sizeof(strategy_trading_action_message::fields_type) == 11, "unexpected sizeof strategy_trading_action_message::fields_type");
static_assert(sizeof(strategy_trading_action_message) == sizeof(itch_topcomboquotefeed::message_header) + 11, "unexpected sizeof strategy_trading_action_message");

#pragma pack(pop)
}
