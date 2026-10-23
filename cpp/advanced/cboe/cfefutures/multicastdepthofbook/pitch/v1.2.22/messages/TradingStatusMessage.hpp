#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/Symbol.hpp"
#include "../types/Reserved2.hpp"
#include "../types/TradingStatus.hpp"
#include "../types/Reserved3.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

namespace pitch_multicastdepthofbook = ::cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22;

#pragma pack(push, 1)

// Trading Status Message
struct trading_status_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::symbol symbol;
        pitch_multicastdepthofbook::reserved_2 reserved_2;
        pitch_multicastdepthofbook::trading_status trading_status;
        pitch_multicastdepthofbook::reserved_3 reserved_3;
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
static_assert(offsetof(trading_status_message::fields_type, symbol) == 4, "unexpected offset of trading_status_message::fields_type::symbol");
static_assert(offsetof(trading_status_message::fields_type, reserved_2) == 10, "unexpected offset of trading_status_message::fields_type::reserved_2");
static_assert(offsetof(trading_status_message::fields_type, trading_status) == 12, "unexpected offset of trading_status_message::fields_type::trading_status");
static_assert(offsetof(trading_status_message::fields_type, reserved_3) == 13, "unexpected offset of trading_status_message::fields_type::reserved_3");
static_assert(sizeof(trading_status_message::fields_type) == 16, "unexpected sizeof trading_status_message::fields_type");
static_assert(sizeof(trading_status_message) == sizeof(pitch_multicastdepthofbook::message_header) + 16, "unexpected sizeof trading_status_message");

#pragma pack(pop)
}
