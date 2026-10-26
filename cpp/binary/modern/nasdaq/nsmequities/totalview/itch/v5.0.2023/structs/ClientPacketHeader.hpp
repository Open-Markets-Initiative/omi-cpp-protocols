#pragma once

#include "../types/PacketLength.hpp"
#include "../types/ClientPacketType.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

struct ClientPacketHeader {

    PacketLength packet_length;
    ClientPacketType client_packet_type;

    // parse method
    static ClientPacketHeader* parse(std::byte* buffer) {
        return reinterpret_cast<ClientPacketHeader*>(buffer);
    }

    // parse method const
    static const ClientPacketHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const ClientPacketHeader*>(buffer);
    }
};

#pragma pack(pop)
}
