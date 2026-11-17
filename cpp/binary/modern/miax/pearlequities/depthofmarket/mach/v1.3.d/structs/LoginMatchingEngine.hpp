// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: structs/LoginMatchingEngine.hpp
#pragma once

#include "../types/LoginStatus.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/HighestSequenceNumber.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

struct LoginMatchingEngine {

    LoginStatus login_status;
    TradingSessionId trading_session_id;
    HighestSequenceNumber highest_sequence_number;

    // parse method
    static LoginMatchingEngine* parse(std::byte* buffer) {
        return reinterpret_cast<LoginMatchingEngine*>(buffer);
    }

    // parse method const
    static const LoginMatchingEngine* parse(const std::byte* buffer) {
        return reinterpret_cast<const LoginMatchingEngine*>(buffer);
    }
};

#pragma pack(pop)
}
