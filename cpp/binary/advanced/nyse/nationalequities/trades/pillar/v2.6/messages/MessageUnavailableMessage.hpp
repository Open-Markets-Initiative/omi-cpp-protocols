#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/BeginSeqNum.hpp"
#include "../types/EndSeqNum.hpp"
#include "../types/ProductId.hpp"
#include "../types/ChannelId.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

namespace pillar_trades = ::nyse::nationalequities::trades::pillar::v2_6;

#pragma pack(push, 1)

// Message Unavailable Message
struct message_unavailable_message {

    struct fields_type {
        pillar_trades::begin_seq_num begin_seq_num;
        pillar_trades::end_seq_num end_seq_num;
        pillar_trades::product_id product_id;
        pillar_trades::channel_id channel_id;
    };

    pillar_trades::message_header header = {std::uint16_t(sizeof(pillar_trades::message_header) + sizeof(fields_type)), message_type::enum_type::message_unavailable_message};

    fields_type fields;

    // parse method
    static message_unavailable_message* parse(std::byte* buffer) {
        return reinterpret_cast<message_unavailable_message*>(buffer);
    }

    // parse method const
    static const message_unavailable_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const message_unavailable_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(message_unavailable_message::fields_type, begin_seq_num) == 0, "unexpected offset of message_unavailable_message::fields_type::begin_seq_num");
static_assert(offsetof(message_unavailable_message::fields_type, end_seq_num) == 4, "unexpected offset of message_unavailable_message::fields_type::end_seq_num");
static_assert(offsetof(message_unavailable_message::fields_type, product_id) == 8, "unexpected offset of message_unavailable_message::fields_type::product_id");
static_assert(offsetof(message_unavailable_message::fields_type, channel_id) == 9, "unexpected offset of message_unavailable_message::fields_type::channel_id");
static_assert(sizeof(message_unavailable_message::fields_type) == 10, "unexpected sizeof message_unavailable_message::fields_type");
static_assert(sizeof(message_unavailable_message) == sizeof(pillar_trades::message_header) + 10, "unexpected sizeof message_unavailable_message");

#pragma pack(pop)
}
