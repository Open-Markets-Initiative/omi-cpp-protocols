#pragma once

#include "../types/NumberOfMatchingEngines.hpp"
#include "../types/LoginStatus.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/HighestSequenceNumber.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

struct LoginResponse {

    NumberOfMatchingEngines number_of_matching_engines;
    LoginStatus login_status;
    TradingSessionId trading_session_id;
    HighestSequenceNumber highest_sequence_number;

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
