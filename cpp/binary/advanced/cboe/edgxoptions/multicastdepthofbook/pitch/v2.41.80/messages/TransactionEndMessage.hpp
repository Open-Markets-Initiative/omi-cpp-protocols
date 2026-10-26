#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

namespace pitch_multicastdepthofbook = ::cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80;

#pragma pack(push, 1)

// Transaction End Message
struct transaction_end_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::transaction_end_message};

    fields_type fields;

    // parse method
    static transaction_end_message* parse(std::byte* buffer) {
        return reinterpret_cast<transaction_end_message*>(buffer);
    }

    // parse method const
    static const transaction_end_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const transaction_end_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(transaction_end_message::fields_type, time_offset) == 0, "unexpected offset of transaction_end_message::fields_type::time_offset");
static_assert(sizeof(transaction_end_message::fields_type) == 4, "unexpected sizeof transaction_end_message::fields_type");
static_assert(sizeof(transaction_end_message) == sizeof(pitch_multicastdepthofbook::message_header) + 4, "unexpected sizeof transaction_end_message");

#pragma pack(pop)
}
