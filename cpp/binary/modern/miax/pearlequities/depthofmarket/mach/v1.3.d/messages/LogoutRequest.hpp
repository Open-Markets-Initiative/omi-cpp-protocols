// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/LogoutRequest.hpp
#pragma once

#include "../types/LogoutReason.hpp"
#include "../structs/EsesmPacketHeader.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

// The client may send a Logout request packet to request the connection be terminated
struct LogoutRequest {

    LogoutReason logout_reason;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'X';

    // parse method
    static LogoutRequest* parse(std::byte* buffer) {
        return reinterpret_cast<LogoutRequest*>(buffer);
    }

    // parse method const
    static const LogoutRequest* parse(const std::byte* buffer) {
        return reinterpret_cast<const LogoutRequest*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LogoutRequest* parse(const EsesmPacketHeader* header) {
        return reinterpret_cast<const LogoutRequest*>(reinterpret_cast<const std::byte*>(header) + sizeof(EsesmPacketHeader));
    }
};

#pragma pack(pop)
}
