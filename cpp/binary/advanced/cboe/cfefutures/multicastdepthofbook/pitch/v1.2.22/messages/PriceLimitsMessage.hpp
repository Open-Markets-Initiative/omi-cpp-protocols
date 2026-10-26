#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/Symbol.hpp"
#include "../types/UpperPriceLimit.hpp"
#include "../types/LowerPriceLimit.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

namespace pitch_multicastdepthofbook = ::cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22;

#pragma pack(push, 1)

// Price Limits Message
struct price_limits_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::symbol symbol;
        pitch_multicastdepthofbook::upper_price_limit upper_price_limit;
        pitch_multicastdepthofbook::lower_price_limit lower_price_limit;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::price_limits_message};

    fields_type fields;

    // parse method
    static price_limits_message* parse(std::byte* buffer) {
        return reinterpret_cast<price_limits_message*>(buffer);
    }

    // parse method const
    static const price_limits_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const price_limits_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(price_limits_message::fields_type, time_offset) == 0, "unexpected offset of price_limits_message::fields_type::time_offset");
static_assert(offsetof(price_limits_message::fields_type, symbol) == 4, "unexpected offset of price_limits_message::fields_type::symbol");
static_assert(offsetof(price_limits_message::fields_type, upper_price_limit) == 10, "unexpected offset of price_limits_message::fields_type::upper_price_limit");
static_assert(offsetof(price_limits_message::fields_type, lower_price_limit) == 18, "unexpected offset of price_limits_message::fields_type::lower_price_limit");
static_assert(sizeof(price_limits_message::fields_type) == 26, "unexpected sizeof price_limits_message::fields_type");
static_assert(sizeof(price_limits_message) == sizeof(pitch_multicastdepthofbook::message_header) + 26, "unexpected sizeof price_limits_message");

#pragma pack(pop)
}
