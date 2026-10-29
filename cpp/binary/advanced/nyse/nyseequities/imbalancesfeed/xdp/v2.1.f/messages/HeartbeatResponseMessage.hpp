#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceId.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f {

namespace xdp_imbalancesfeed = ::nyse::nyseequities::imbalancesfeed::xdp::v2_1_f;

#pragma pack(push, 1)

// Heartbeat Response Message
struct heartbeat_response_message {

    struct fields_type {
        xdp_imbalancesfeed::source_id source_id;
    };

    xdp_imbalancesfeed::message_header header = {std::uint16_t(sizeof(xdp_imbalancesfeed::message_header) + sizeof(fields_type)), message_type::enum_type::heartbeat_response_message};

    fields_type fields;

    // parse method
    static heartbeat_response_message* parse(std::byte* buffer) {
        return reinterpret_cast<heartbeat_response_message*>(buffer);
    }

    // parse method const
    static const heartbeat_response_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const heartbeat_response_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(heartbeat_response_message::fields_type, source_id) == 0, "unexpected offset of heartbeat_response_message::fields_type::source_id");
static_assert(sizeof(heartbeat_response_message::fields_type) == 10, "unexpected sizeof heartbeat_response_message::fields_type");
static_assert(sizeof(heartbeat_response_message) == sizeof(xdp_imbalancesfeed::message_header) + 10, "unexpected sizeof heartbeat_response_message");

#pragma pack(pop)
}
