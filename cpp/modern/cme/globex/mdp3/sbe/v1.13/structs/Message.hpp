#pragma once

#include "../types/MessageSize.hpp"
#include "../structs/MessageHeader.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct Message {

    MessageSize message_size;
    MessageHeader message_header;

    // parse method
    static Message* parse(std::byte* buffer) {
        return reinterpret_cast<Message*>(buffer);
    }

    // parse method const
    static const Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const Message*>(buffer);
    }
};

#pragma pack(pop)
}
