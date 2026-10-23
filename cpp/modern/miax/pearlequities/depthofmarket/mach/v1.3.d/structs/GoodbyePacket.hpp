#pragma once

#include "../types/LogoutReason.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

struct GoodbyePacket {

    LogoutReason logout_reason;

    // parse method
    static GoodbyePacket* parse(std::byte* buffer) {
        return reinterpret_cast<GoodbyePacket*>(buffer);
    }

    // parse method const
    static const GoodbyePacket* parse(const std::byte* buffer) {
        return reinterpret_cast<const GoodbyePacket*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const GoodbyePacket* parse(const EsesmPacketHeader* header) {
        return reinterpret_cast<const GoodbyePacket*>(reinterpret_cast<const std::byte*>(header) + sizeof(EsesmPacketHeader));
    }
};

#pragma pack(pop)
}
