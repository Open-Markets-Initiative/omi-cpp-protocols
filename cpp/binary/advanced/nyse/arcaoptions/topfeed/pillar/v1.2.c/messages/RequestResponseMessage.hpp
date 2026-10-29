#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/RequestSeqNum.hpp"
#include "../types/BeginSeqNum.hpp"
#include "../types/EndSeqNum.hpp"
#include "../types/SourceId.hpp"
#include "../types/ProductId.hpp"
#include "../types/ChannelId.hpp"
#include "../types/Status.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

namespace pillar_topfeed = ::nyse::arcaoptions::topfeed::pillar::v1_2_c;

#pragma pack(push, 1)

// Request Response Message
struct request_response_message {

    struct fields_type {
        pillar_topfeed::request_seq_num request_seq_num;
        pillar_topfeed::begin_seq_num begin_seq_num;
        pillar_topfeed::end_seq_num end_seq_num;
        pillar_topfeed::source_id source_id;
        pillar_topfeed::product_id product_id;
        pillar_topfeed::channel_id channel_id;
        pillar_topfeed::status status;
    };

    pillar_topfeed::message_header header = {std::uint16_t(sizeof(pillar_topfeed::message_header) + sizeof(fields_type)), message_type::enum_type::request_response_message};

    fields_type fields;

    // parse method
    static request_response_message* parse(std::byte* buffer) {
        return reinterpret_cast<request_response_message*>(buffer);
    }

    // parse method const
    static const request_response_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const request_response_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(request_response_message::fields_type, request_seq_num) == 0, "unexpected offset of request_response_message::fields_type::request_seq_num");
static_assert(offsetof(request_response_message::fields_type, begin_seq_num) == 4, "unexpected offset of request_response_message::fields_type::begin_seq_num");
static_assert(offsetof(request_response_message::fields_type, end_seq_num) == 8, "unexpected offset of request_response_message::fields_type::end_seq_num");
static_assert(offsetof(request_response_message::fields_type, source_id) == 12, "unexpected offset of request_response_message::fields_type::source_id");
static_assert(offsetof(request_response_message::fields_type, product_id) == 22, "unexpected offset of request_response_message::fields_type::product_id");
static_assert(offsetof(request_response_message::fields_type, channel_id) == 23, "unexpected offset of request_response_message::fields_type::channel_id");
static_assert(offsetof(request_response_message::fields_type, status) == 24, "unexpected offset of request_response_message::fields_type::status");
static_assert(sizeof(request_response_message::fields_type) == 25, "unexpected sizeof request_response_message::fields_type");
static_assert(sizeof(request_response_message) == sizeof(pillar_topfeed::message_header) + 25, "unexpected sizeof request_response_message");

#pragma pack(pop)
}
