#pragma once

#include "../types/SesmPacketLength.hpp"
#include "../types/SesmPacketType.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

#pragma pack(push, 1)

struct SesmPacketHeader {

    SesmPacketLength sesm_packet_length;
    SesmPacketType sesm_packet_type;

    // parse method
    static SesmPacketHeader* parse(std::byte* buffer) {
        return reinterpret_cast<SesmPacketHeader*>(buffer);
    }

    // parse method const
    static const SesmPacketHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const SesmPacketHeader*>(buffer);
    }
};

#pragma pack(pop)
}
