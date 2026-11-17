// Nasdaq.NsmEquities.TotalView.Itch.v5.0.2026: structs/ServerPacketHeader.hpp
#pragma once

#include "../types/PacketLength.hpp"
#include "../types/ServerPacketType.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

#pragma pack(push, 1)

struct ServerPacketHeader {

    PacketLength packet_length;
    ServerPacketType server_packet_type;

    // parse method
    static ServerPacketHeader* parse(std::byte* buffer) {
        return reinterpret_cast<ServerPacketHeader*>(buffer);
    }

    // parse method const
    static const ServerPacketHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const ServerPacketHeader*>(buffer);
    }
};

#pragma pack(pop)
}
