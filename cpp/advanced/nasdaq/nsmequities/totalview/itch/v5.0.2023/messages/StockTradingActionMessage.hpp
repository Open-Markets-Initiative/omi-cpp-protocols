#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Stock.hpp"
#include "../types/TradingState.hpp"
#include "../types/Reserved.hpp"
#include "../types/ReasonCode.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

#pragma pack(push, 1)

// Stock Trading Action Message
struct stock_trading_action_message {

    struct fields_type {
        itch_totalview::stock_locate stock_locate;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::timestamp timestamp;
        itch_totalview::stock stock;
        itch_totalview::trading_state trading_state;
        itch_totalview::reserved reserved;
        itch_totalview::reason_code reason_code;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::stock_trading_action_message};

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
static_assert(offsetof(stock_trading_action_message::fields_type, stock_locate) == 0, "unexpected offset of stock_trading_action_message::fields_type::stock_locate");
static_assert(offsetof(stock_trading_action_message::fields_type, tracking_number) == 2, "unexpected offset of stock_trading_action_message::fields_type::tracking_number");
static_assert(offsetof(stock_trading_action_message::fields_type, timestamp) == 4, "unexpected offset of stock_trading_action_message::fields_type::timestamp");
static_assert(offsetof(stock_trading_action_message::fields_type, stock) == 10, "unexpected offset of stock_trading_action_message::fields_type::stock");
static_assert(offsetof(stock_trading_action_message::fields_type, trading_state) == 18, "unexpected offset of stock_trading_action_message::fields_type::trading_state");
static_assert(offsetof(stock_trading_action_message::fields_type, reserved) == 19, "unexpected offset of stock_trading_action_message::fields_type::reserved");
static_assert(offsetof(stock_trading_action_message::fields_type, reason_code) == 20, "unexpected offset of stock_trading_action_message::fields_type::reason_code");
static_assert(sizeof(stock_trading_action_message::fields_type) == 24, "unexpected sizeof stock_trading_action_message::fields_type");
static_assert(sizeof(stock_trading_action_message) == sizeof(message_header) + 24, "unexpected sizeof stock_trading_action_message");

#pragma pack(pop)
}
