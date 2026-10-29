#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/Stock.hpp"
#include "../types/TradingState.hpp"
#include "../types/Reserved.hpp"
#include "../types/Reason.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v4_0;

#pragma pack(push, 1)

// Stock Trading Action Message
struct stock_trading_action_message {

    struct fields_type {
        itch_totalview::nanoseconds nanoseconds;
        itch_totalview::stock stock;
        itch_totalview::trading_state trading_state;
        itch_totalview::reserved reserved;
        itch_totalview::reason reason;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::stock_trading_action_message};

    fields_type fields;

    // parse method
    static stock_trading_action_message* parse(std::byte* buffer) {
        return reinterpret_cast<stock_trading_action_message*>(buffer);
    }

    // parse method const
    static const stock_trading_action_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const stock_trading_action_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(stock_trading_action_message::fields_type, nanoseconds) == 0, "unexpected offset of stock_trading_action_message::fields_type::nanoseconds");
static_assert(offsetof(stock_trading_action_message::fields_type, stock) == 4, "unexpected offset of stock_trading_action_message::fields_type::stock");
static_assert(offsetof(stock_trading_action_message::fields_type, trading_state) == 10, "unexpected offset of stock_trading_action_message::fields_type::trading_state");
static_assert(offsetof(stock_trading_action_message::fields_type, reserved) == 11, "unexpected offset of stock_trading_action_message::fields_type::reserved");
static_assert(offsetof(stock_trading_action_message::fields_type, reason) == 12, "unexpected offset of stock_trading_action_message::fields_type::reason");
static_assert(sizeof(stock_trading_action_message::fields_type) == 16, "unexpected sizeof stock_trading_action_message::fields_type");
static_assert(sizeof(stock_trading_action_message) == sizeof(itch_totalview::message_header) + 16, "unexpected sizeof stock_trading_action_message");

#pragma pack(pop)
}
