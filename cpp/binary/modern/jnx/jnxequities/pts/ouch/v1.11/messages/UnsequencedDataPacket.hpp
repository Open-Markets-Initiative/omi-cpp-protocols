#pragma once

#include "../types/UnsequencedMessageType.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

#pragma pack(push, 1)

// The Unsequenced Data Packets act as an envelope to carry the actual data messages that are transferred from the client to the server
struct UnsequencedDataPacket {

    UnsequencedMessageType unsequenced_message_type;

    // parse method
    static UnsequencedDataPacket* parse(std::byte* buffer) {
        return reinterpret_cast<UnsequencedDataPacket*>(buffer);
    }

    // parse method const
    static const UnsequencedDataPacket* parse(const std::byte* buffer) {
        return reinterpret_cast<const UnsequencedDataPacket*>(buffer);
    }
};

#pragma pack(pop)
}
