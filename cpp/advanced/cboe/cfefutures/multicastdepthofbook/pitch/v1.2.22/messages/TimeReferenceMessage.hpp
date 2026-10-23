#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/MidnightReference.hpp"
#include "../types/TimeReference.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/TradeDate.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

namespace pitch_multicastdepthofbook = ::cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22;

#pragma pack(push, 1)

// Time Reference Message
struct time_reference_message {

    struct fields_type {
        pitch_multicastdepthofbook::midnight_reference midnight_reference;
        pitch_multicastdepthofbook::time_reference time_reference;
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::trade_date trade_date;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::time_reference_message};

    fields_type fields;

    // parse method
    static time_reference_message* parse(std::byte* buffer) {
        return reinterpret_cast<time_reference_message*>(buffer);
    }

    // parse method const
    static const time_reference_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const time_reference_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(time_reference_message::fields_type, midnight_reference) == 0, "unexpected offset of time_reference_message::fields_type::midnight_reference");
static_assert(offsetof(time_reference_message::fields_type, time_reference) == 4, "unexpected offset of time_reference_message::fields_type::time_reference");
static_assert(offsetof(time_reference_message::fields_type, time_offset) == 8, "unexpected offset of time_reference_message::fields_type::time_offset");
static_assert(offsetof(time_reference_message::fields_type, trade_date) == 12, "unexpected offset of time_reference_message::fields_type::trade_date");
static_assert(sizeof(time_reference_message::fields_type) == 16, "unexpected sizeof time_reference_message::fields_type");
static_assert(sizeof(time_reference_message) == sizeof(pitch_multicastdepthofbook::message_header) + 16, "unexpected sizeof time_reference_message");

#pragma pack(pop)
}
