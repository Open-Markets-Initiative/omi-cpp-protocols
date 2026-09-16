#pragma once

#include <cstddef>
#include "../types/TagLength.hpp"
#include "../types/MessageType.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

namespace flex_marketbyorder = ::jpx::tseequities::marketbyorder::flex::v1_1;

#pragma pack(push, 1)

struct message_header {

    flex_marketbyorder::tag_length tag_length;
    flex_marketbyorder::message_type message_type;

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
static_assert(offsetof(message_header, tag_length) == 0, "unexpected offset of message_header::tag_length");
static_assert(offsetof(message_header, message_type) == 1, "unexpected offset of message_header::message_type");
static_assert(sizeof(message_header) == 2, "unexpected sizeof message_header");

#pragma pack(pop)
}
