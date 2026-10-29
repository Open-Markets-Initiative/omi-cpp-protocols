#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/StreamId.hpp"
#include "../types/Reserved2.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

namespace xdp_complexfeed = ::nyse::amexoptions::complexfeed::xdp::v1_3_a;

#pragma pack(push, 1)

// Stream Id Message
struct stream_id_message {

    struct fields_type {
        xdp_complexfeed::stream_id stream_id;
        xdp_complexfeed::reserved_2 reserved_2;
    };

    xdp_complexfeed::message_header header = {std::uint16_t(sizeof(xdp_complexfeed::message_header) + sizeof(fields_type)), message_type::enum_type::stream_id_message};

    fields_type fields;

    // parse method
    static stream_id_message* parse(std::byte* buffer) {
        return reinterpret_cast<stream_id_message*>(buffer);
    }

    // parse method const
    static const stream_id_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const stream_id_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(stream_id_message::fields_type, stream_id) == 0, "unexpected offset of stream_id_message::fields_type::stream_id");
static_assert(offsetof(stream_id_message::fields_type, reserved_2) == 2, "unexpected offset of stream_id_message::fields_type::reserved_2");
static_assert(sizeof(stream_id_message::fields_type) == 4, "unexpected sizeof stream_id_message::fields_type");
static_assert(sizeof(stream_id_message) == sizeof(xdp_complexfeed::message_header) + 4, "unexpected sizeof stream_id_message");

#pragma pack(pop)
}
