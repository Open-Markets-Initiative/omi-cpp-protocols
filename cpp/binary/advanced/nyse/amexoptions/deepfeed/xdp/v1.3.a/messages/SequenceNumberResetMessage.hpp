#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/ProductId.hpp"
#include "../types/ChannelId.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

namespace xdp_deepfeed = ::nyse::amexoptions::deepfeed::xdp::v1_3_a;

#pragma pack(push, 1)

// Sequence Number Reset Message
struct sequence_number_reset_message {

    struct fields_type {
        xdp_deepfeed::source_time source_time;
        xdp_deepfeed::source_time_ns source_time_ns;
        xdp_deepfeed::product_id product_id;
        xdp_deepfeed::channel_id channel_id;
    };

    xdp_deepfeed::message_header header = {std::uint16_t(sizeof(xdp_deepfeed::message_header) + sizeof(fields_type)), message_type::enum_type::sequence_number_reset_message};

    fields_type fields;

    // parse method
    static sequence_number_reset_message* parse(std::byte* buffer) {
        return reinterpret_cast<sequence_number_reset_message*>(buffer);
    }

    // parse method const
    static const sequence_number_reset_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const sequence_number_reset_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(sequence_number_reset_message::fields_type, source_time) == 0, "unexpected offset of sequence_number_reset_message::fields_type::source_time");
static_assert(offsetof(sequence_number_reset_message::fields_type, source_time_ns) == 4, "unexpected offset of sequence_number_reset_message::fields_type::source_time_ns");
static_assert(offsetof(sequence_number_reset_message::fields_type, product_id) == 8, "unexpected offset of sequence_number_reset_message::fields_type::product_id");
static_assert(offsetof(sequence_number_reset_message::fields_type, channel_id) == 9, "unexpected offset of sequence_number_reset_message::fields_type::channel_id");
static_assert(sizeof(sequence_number_reset_message::fields_type) == 10, "unexpected sizeof sequence_number_reset_message::fields_type");
static_assert(sizeof(sequence_number_reset_message) == sizeof(xdp_deepfeed::message_header) + 10, "unexpected sizeof sequence_number_reset_message");

#pragma pack(pop)
}
