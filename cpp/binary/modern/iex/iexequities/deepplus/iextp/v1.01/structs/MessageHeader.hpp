#pragma once

#include "../types/MessageLength.hpp"
#include "../types/MessageType.hpp"

namespace iex::iexequities::deepplus::iextp::v1_01 {

#pragma pack(push, 1)

struct MessageHeader {

    MessageLength message_length;
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
