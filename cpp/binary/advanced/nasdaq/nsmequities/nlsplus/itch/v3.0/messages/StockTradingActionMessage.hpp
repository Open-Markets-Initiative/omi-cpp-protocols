#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Reserved.hpp"
#include "../types/IssueSymbol.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/CurrentTradingState.hpp"
#include "../types/Reason.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

// Stock Trading Action Message
struct stock_trading_action_message {

    struct fields_type {
        itch_nlsplus::reserved reserved;
        itch_nlsplus::issue_symbol issue_symbol;
        itch_nlsplus::security_class security_class;
        itch_nlsplus::current_trading_state current_trading_state;
        itch_nlsplus::reason reason;
    };

    itch_nlsplus::message_header header = {std::uint16_t(sizeof(itch_nlsplus::message_header) + sizeof(fields_type) - 2), {}, {}, message_type::enum_type::stock_trading_action_message};

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
static_assert(offsetof(stock_trading_action_message::fields_type, reserved) == 0, "unexpected offset of stock_trading_action_message::fields_type::reserved");
static_assert(offsetof(stock_trading_action_message::fields_type, issue_symbol) == 1, "unexpected offset of stock_trading_action_message::fields_type::issue_symbol");
static_assert(offsetof(stock_trading_action_message::fields_type, security_class) == 9, "unexpected offset of stock_trading_action_message::fields_type::security_class");
static_assert(offsetof(stock_trading_action_message::fields_type, current_trading_state) == 10, "unexpected offset of stock_trading_action_message::fields_type::current_trading_state");
static_assert(offsetof(stock_trading_action_message::fields_type, reason) == 11, "unexpected offset of stock_trading_action_message::fields_type::reason");
static_assert(sizeof(stock_trading_action_message::fields_type) == 15, "unexpected sizeof stock_trading_action_message::fields_type");
static_assert(sizeof(stock_trading_action_message) == sizeof(itch_nlsplus::message_header) + 15, "unexpected sizeof stock_trading_action_message");

#pragma pack(pop)
}
