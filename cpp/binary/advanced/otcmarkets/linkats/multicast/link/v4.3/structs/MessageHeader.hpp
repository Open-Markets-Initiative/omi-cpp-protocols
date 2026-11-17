// OtcMarkets.LinkAts.Multicast.Link.v4.3: structs/MessageHeader.hpp
#pragma once

#include <cstddef>
#include "../types/MessageSize.hpp"
#include "../types/MessageType.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

namespace link_multicast = ::otcmarkets::linkats::multicast::link::v4_3;

#pragma pack(push, 1)

struct message_header {

    link_multicast::message_size message_size;
    link_multicast::message_type message_type;

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
static_assert(sizeof(message_header) == 3, "unexpected sizeof message_header");

#pragma pack(pop)
}
