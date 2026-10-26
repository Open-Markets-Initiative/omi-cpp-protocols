#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/Symbol.hpp"
#include "../types/TradeDate.hpp"
#include "../types/OpenInterest.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

namespace pitch_multicastdepthofbook = ::cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22;

#pragma pack(push, 1)

// Open Interest Message
struct open_interest_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::symbol symbol;
        pitch_multicastdepthofbook::trade_date trade_date;
        pitch_multicastdepthofbook::open_interest open_interest;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::open_interest_message};

    fields_type fields;

    // parse method
    static open_interest_message* parse(std::byte* buffer) {
        return reinterpret_cast<open_interest_message*>(buffer);
    }

    // parse method const
    static const open_interest_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const open_interest_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(open_interest_message::fields_type, time_offset) == 0, "unexpected offset of open_interest_message::fields_type::time_offset");
static_assert(offsetof(open_interest_message::fields_type, symbol) == 4, "unexpected offset of open_interest_message::fields_type::symbol");
static_assert(offsetof(open_interest_message::fields_type, trade_date) == 10, "unexpected offset of open_interest_message::fields_type::trade_date");
static_assert(offsetof(open_interest_message::fields_type, open_interest) == 14, "unexpected offset of open_interest_message::fields_type::open_interest");
static_assert(sizeof(open_interest_message::fields_type) == 18, "unexpected sizeof open_interest_message::fields_type");
static_assert(sizeof(open_interest_message) == sizeof(pitch_multicastdepthofbook::message_header) + 18, "unexpected sizeof open_interest_message");

#pragma pack(pop)
}
