// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: structs/RequestedMatchingEngine.hpp
#pragma once

#include "../types/RequestedTradingSessionId.hpp"
#include "../types/RequestedSequenceNumber.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

struct RequestedMatchingEngine {

    RequestedTradingSessionId requested_trading_session_id;
    RequestedSequenceNumber requested_sequence_number;

    // parse method
    static RequestedMatchingEngine* parse(std::byte* buffer) {
        return reinterpret_cast<RequestedMatchingEngine*>(buffer);
    }

    // parse method const
    static const RequestedMatchingEngine* parse(const std::byte* buffer) {
        return reinterpret_cast<const RequestedMatchingEngine*>(buffer);
    }
};

#pragma pack(pop)
}
