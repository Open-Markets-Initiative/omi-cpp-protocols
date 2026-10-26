#pragma once

#include "../types/EsesmPacketLength.hpp"
#include "../types/EsesmPacketType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

struct EsesmPacketHeader {

    EsesmPacketLength esesm_packet_length;
    EsesmPacketType esesm_packet_type;

    // parse method
    static EsesmPacketHeader* parse(std::byte* buffer) {
        return reinterpret_cast<EsesmPacketHeader*>(buffer);
    }

    // parse method const
    static const EsesmPacketHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const EsesmPacketHeader*>(buffer);
    }
};

#pragma pack(pop)
}
