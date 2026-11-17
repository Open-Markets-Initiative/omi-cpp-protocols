// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/GoodbyePacket.hpp
#pragma once

#include "../types/GoodbyeReason.hpp"
#include "../structs/EsesmPacketHeader.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

// The server may send a GoodBye packet to inform the client a reason for termination of the connection just before it terminates the connection
struct GoodbyePacket {

    GoodbyeReason goodbye_reason;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'G';

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
