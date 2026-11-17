// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/LoginRequest.hpp
#pragma once

#include "../types/EsesmVersion.hpp"
#include "../types/Username.hpp"
#include "../types/ComputerId.hpp"
#include "../types/ApplicationProtocol.hpp"
#include "../types/NumberOfMatchingEngines.hpp"
#include "../structs/EsesmPacketHeader.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

// The ESesM client must send a Login request packet immediately upon establishing a new TCP/IP socket connection to the server
struct LoginRequest {

    EsesmVersion esesm_version;
    Username username;
    ComputerId computer_id;
    ApplicationProtocol application_protocol;
    NumberOfMatchingEngines number_of_matching_engines;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'l';

    // parse method
    static LoginRequest* parse(std::byte* buffer) {
        return reinterpret_cast<LoginRequest*>(buffer);
    }

    // parse method const
    static const LoginRequest* parse(const std::byte* buffer) {
        return reinterpret_cast<const LoginRequest*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LoginRequest* parse(const EsesmPacketHeader* header) {
        return reinterpret_cast<const LoginRequest*>(reinterpret_cast<const std::byte*>(header) + sizeof(EsesmPacketHeader));
    }
};

#pragma pack(pop)
}
