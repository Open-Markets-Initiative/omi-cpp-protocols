// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/TradingSessionUpdate.hpp
#pragma once

#include "../types/MatchingEngineId.hpp"
#include "../types/TradingSessionId.hpp"
#include "../structs/EsesmPacketHeader.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

// The ESesM server sends a Trading Session Update packet to inform the client that a new trading session is starting on the specified Matching Engine
struct TradingSessionUpdate {

    MatchingEngineId matching_engine_id;
    TradingSessionId trading_session_id;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'u';

    // parse method
    static TradingSessionUpdate* parse(std::byte* buffer) {
        return reinterpret_cast<TradingSessionUpdate*>(buffer);
    }

    // parse method const
    static const TradingSessionUpdate* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradingSessionUpdate*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradingSessionUpdate* parse(const EsesmPacketHeader* header) {
        return reinterpret_cast<const TradingSessionUpdate*>(reinterpret_cast<const std::byte*>(header) + sizeof(EsesmPacketHeader));
    }
};

#pragma pack(pop)
}
