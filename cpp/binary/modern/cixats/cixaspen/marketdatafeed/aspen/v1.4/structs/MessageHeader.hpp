#pragma once

#include "../types/Length.hpp"
#include "../types/MessageType.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

#pragma pack(push, 1)

struct MessageHeader {

    Length length;
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
