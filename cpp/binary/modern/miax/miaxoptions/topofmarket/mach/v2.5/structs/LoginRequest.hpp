#pragma once

#include "../types/SesmVersion.hpp"
#include "../types/Username.hpp"
#include "../types/ComputerId.hpp"
#include "../types/ApplicationProtocol.hpp"
#include "../types/RequestedTradingSessionId.hpp"
#include "../types/RequestedSequenceNumber.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

#pragma pack(push, 1)

struct LoginRequest {

    SesmVersion sesm_version;
    Username username;
    ComputerId computer_id;
    ApplicationProtocol application_protocol;
    RequestedTradingSessionId requested_trading_session_id;
    RequestedSequenceNumber requested_sequence_number;

    // parse method
    static LoginRequest* parse(std::byte* buffer) {
        return reinterpret_cast<LoginRequest*>(buffer);
    }

    // parse method const
    static const LoginRequest* parse(const std::byte* buffer) {
        return reinterpret_cast<const LoginRequest*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LoginRequest* parse(const SesmPacketHeader* header) {
        return reinterpret_cast<const LoginRequest*>(reinterpret_cast<const std::byte*>(header) + sizeof(SesmPacketHeader));
    }
};

#pragma pack(pop)
}
