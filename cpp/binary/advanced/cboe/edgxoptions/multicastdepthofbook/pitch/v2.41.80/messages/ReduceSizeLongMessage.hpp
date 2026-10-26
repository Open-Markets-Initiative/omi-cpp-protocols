#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/CanceledQuantityLong.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

namespace pitch_multicastdepthofbook = ::cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80;

#pragma pack(push, 1)

// Reduce Size Long Message
struct reduce_size_long_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::order_id order_id;
        pitch_multicastdepthofbook::canceled_quantity_long canceled_quantity_long;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::reduce_size_long_message};

    fields_type fields;

    // parse method
    static reduce_size_long_message* parse(std::byte* buffer) {
        return reinterpret_cast<reduce_size_long_message*>(buffer);
    }

    // parse method const
    static const reduce_size_long_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const reduce_size_long_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(reduce_size_long_message::fields_type, time_offset) == 0, "unexpected offset of reduce_size_long_message::fields_type::time_offset");
static_assert(offsetof(reduce_size_long_message::fields_type, order_id) == 4, "unexpected offset of reduce_size_long_message::fields_type::order_id");
static_assert(offsetof(reduce_size_long_message::fields_type, canceled_quantity_long) == 12, "unexpected offset of reduce_size_long_message::fields_type::canceled_quantity_long");
static_assert(sizeof(reduce_size_long_message::fields_type) == 16, "unexpected sizeof reduce_size_long_message::fields_type");
static_assert(sizeof(reduce_size_long_message) == sizeof(pitch_multicastdepthofbook::message_header) + 16, "unexpected sizeof reduce_size_long_message");

#pragma pack(pop)
}
