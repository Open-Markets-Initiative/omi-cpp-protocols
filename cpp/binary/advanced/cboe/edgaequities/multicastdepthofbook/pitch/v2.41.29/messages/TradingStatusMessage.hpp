#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/SymbolLong.hpp"
#include "../types/TradingStatus.hpp"
#include "../types/RegShoAction.hpp"
#include "../types/Padding.hpp"

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

namespace pitch_multicastdepthofbook = ::cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29;

#pragma pack(push, 1)

// Trading Status Message
struct trading_status_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::symbol_long symbol_long;
        pitch_multicastdepthofbook::trading_status trading_status;
        pitch_multicastdepthofbook::reg_sho_action reg_sho_action;
        pitch_multicastdepthofbook::padding padding;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::trading_status_message};

    fields_type fields;

    // parse method
    static trading_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<trading_status_message*>(buffer);
    }

    // parse method const
    static const trading_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trading_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trading_status_message::fields_type, time_offset) == 0, "unexpected offset of trading_status_message::fields_type::time_offset");
static_assert(offsetof(trading_status_message::fields_type, symbol_long) == 4, "unexpected offset of trading_status_message::fields_type::symbol_long");
static_assert(offsetof(trading_status_message::fields_type, trading_status) == 12, "unexpected offset of trading_status_message::fields_type::trading_status");
static_assert(offsetof(trading_status_message::fields_type, reg_sho_action) == 13, "unexpected offset of trading_status_message::fields_type::reg_sho_action");
static_assert(offsetof(trading_status_message::fields_type, padding) == 14, "unexpected offset of trading_status_message::fields_type::padding");
static_assert(sizeof(trading_status_message::fields_type) == 16, "unexpected sizeof trading_status_message::fields_type");
static_assert(sizeof(trading_status_message) == sizeof(pitch_multicastdepthofbook::message_header) + 16, "unexpected sizeof trading_status_message");

#pragma pack(pop)
}
