#pragma once

#include "../types/MessageSize.hpp"
#include "../types/MessageType.hpp"

namespace nyse::arcaequities::bbo::xdp::v2_4_c {

#pragma pack(push, 1)

struct MessageHeader {

    MessageSize message_size;
    MessageType message_type;

    // parse method
    static MessageHeader* parse(std::byte* buffer) {
        return reinterpret_cast<MessageHeader*>(buffer);
    }

    // parse method const
    static const MessageHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const MessageHeader*>(buffer);
    }
};

#pragma pack(pop)
}
