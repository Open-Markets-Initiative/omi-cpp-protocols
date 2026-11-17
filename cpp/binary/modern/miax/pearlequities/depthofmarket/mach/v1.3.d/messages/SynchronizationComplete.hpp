// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/SynchronizationComplete.hpp
#pragma once

#include "../types/MatchingEngineId.hpp"
#include "../structs/EsesmPacketHeader.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

// The ESesM server sends a Synchronization complete packet when it is done replaying all the old packets and is ready to start sending new packets from the Matching Engine
struct SynchronizationComplete {

    MatchingEngineId matching_engine_id;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'c';

    // parse method
    static SynchronizationComplete* parse(std::byte* buffer) {
        return reinterpret_cast<SynchronizationComplete*>(buffer);
    }

    // parse method const
    static const SynchronizationComplete* parse(const std::byte* buffer) {
        return reinterpret_cast<const SynchronizationComplete*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SynchronizationComplete* parse(const EsesmPacketHeader* header) {
        return reinterpret_cast<const SynchronizationComplete*>(reinterpret_cast<const std::byte*>(header) + sizeof(EsesmPacketHeader));
    }
};

#pragma pack(pop)
}
