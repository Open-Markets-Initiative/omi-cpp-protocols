#pragma once

#include "../types/MessageLength.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/MessageType.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

struct MessageHeader {

    MessageLength message_length;
    TrackingNumber tracking_number;
    Timestamp timestamp;
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
