#pragma once

#include <cstddef>
#include "../types/MessageSize.hpp"
#include "../types/MessageType.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

namespace xdp_imbalancesfeed = ::nyse::nyseequities::imbalancesfeed::xdp::v2_2_a;

#pragma pack(push, 1)

struct message_header {

    xdp_imbalancesfeed::message_size message_size;
    xdp_imbalancesfeed::message_type message_type;

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
