#pragma once

#include "../types/UnsequencedMessageType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

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

    // parse the overlaid body from its selecting header
    static const UnsequencedDataPacket* parse(const EsesmPacketHeader* header) {
        return reinterpret_cast<const UnsequencedDataPacket*>(reinterpret_cast<const std::byte*>(header) + sizeof(EsesmPacketHeader));
    }
};

#pragma pack(pop)
}
