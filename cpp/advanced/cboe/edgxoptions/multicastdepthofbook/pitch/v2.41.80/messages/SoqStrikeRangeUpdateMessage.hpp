#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/SoqIdentifier.hpp"
#include "../types/LowerStrikePrice.hpp"
#include "../types/UpperStrikePrice.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

namespace pitch_multicastdepthofbook = ::cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80;

#pragma pack(push, 1)

// Soq Strike Range Update Message
struct soq_strike_range_update_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::soq_identifier soq_identifier;
        pitch_multicastdepthofbook::lower_strike_price lower_strike_price;
        pitch_multicastdepthofbook::upper_strike_price upper_strike_price;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::soq_strike_range_update_message};

    fields_type fields;

    // parse method
    static soq_strike_range_update_message* parse(std::byte* buffer) {
        return reinterpret_cast<soq_strike_range_update_message*>(buffer);
    }

    // parse method const
    static const soq_strike_range_update_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const soq_strike_range_update_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(soq_strike_range_update_message::fields_type, time_offset) == 0, "unexpected offset of soq_strike_range_update_message::fields_type::time_offset");
static_assert(offsetof(soq_strike_range_update_message::fields_type, soq_identifier) == 4, "unexpected offset of soq_strike_range_update_message::fields_type::soq_identifier");
static_assert(offsetof(soq_strike_range_update_message::fields_type, lower_strike_price) == 24, "unexpected offset of soq_strike_range_update_message::fields_type::lower_strike_price");
static_assert(offsetof(soq_strike_range_update_message::fields_type, upper_strike_price) == 32, "unexpected offset of soq_strike_range_update_message::fields_type::upper_strike_price");
static_assert(sizeof(soq_strike_range_update_message::fields_type) == 40, "unexpected sizeof soq_strike_range_update_message::fields_type");
static_assert(sizeof(soq_strike_range_update_message) == sizeof(pitch_multicastdepthofbook::message_header) + 40, "unexpected sizeof soq_strike_range_update_message");

#pragma pack(pop)
}
