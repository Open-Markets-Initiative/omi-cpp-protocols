#pragma once

#include <cstddef>
#include "../types/MessageSize.hpp"
#include "../types/MessageType.hpp"

namespace nyse::nyseequities::integratedfeedrefresh::pillar::v2_5_g {

namespace pillar_integratedfeedrefresh = ::nyse::nyseequities::integratedfeedrefresh::pillar::v2_5_g;

#pragma pack(push, 1)

struct message_header {

    pillar_integratedfeedrefresh::message_size message_size;
    pillar_integratedfeedrefresh::message_type message_type;

    // parse method
    static message_header* parse(std::byte* buffer) {
        return reinterpret_cast<message_header*>(buffer);
    }

    // parse method const
    static const message_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const message_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(message_header, message_size) == 0, "unexpected offset of message_header::message_size");
static_assert(offsetof(message_header, message_type) == 2, "unexpected offset of message_header::message_type");
static_assert(sizeof(message_header) == 4, "unexpected sizeof message_header");

#pragma pack(pop)
}
