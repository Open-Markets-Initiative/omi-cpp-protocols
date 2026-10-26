#pragma once

#include "../types/MessageSize.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v8 {

#pragma pack(push, 1)

struct MessageHeader {

    MessageSize message_size;
    SimpleBinaryHeader simple_binary_header;

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
