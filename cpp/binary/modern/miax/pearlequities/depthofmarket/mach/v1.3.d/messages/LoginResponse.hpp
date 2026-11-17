// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/LoginResponse.hpp
#pragma once

#include "../types/NumberOfMatchingEngines.hpp"
#include "../structs/EsesmPacketHeader.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

// The ESesM server sends a Login response packet in response to a Login request packet from the client
struct LoginResponse {

    NumberOfMatchingEngines number_of_matching_engines;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'r';

    // parse method
    static LoginResponse* parse(std::byte* buffer) {
        return reinterpret_cast<LoginResponse*>(buffer);
    }

    // parse method const
    static const LoginResponse* parse(const std::byte* buffer) {
        return reinterpret_cast<const LoginResponse*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LoginResponse* parse(const EsesmPacketHeader* header) {
        return reinterpret_cast<const LoginResponse*>(reinterpret_cast<const std::byte*>(header) + sizeof(EsesmPacketHeader));
    }
};

#pragma pack(pop)
}
