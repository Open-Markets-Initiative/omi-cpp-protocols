#pragma once

#include "../types/PacketLength.hpp"
#include "../types/PacketType.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

#pragma pack(push, 1)

struct TcpPacketHeader {

    PacketLength packet_length;
    PacketType packet_type;

    // parse method
    static TcpPacketHeader* parse(std::byte* buffer) {
        return reinterpret_cast<TcpPacketHeader*>(buffer);
    }

    // parse method const
    static const TcpPacketHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const TcpPacketHeader*>(buffer);
    }
};

#pragma pack(pop)
}
