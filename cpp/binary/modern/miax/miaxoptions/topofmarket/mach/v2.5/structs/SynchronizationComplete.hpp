#pragma once

#include "../types/NumberOfMatchingEngines.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

#pragma pack(push, 1)

struct SynchronizationComplete {

    NumberOfMatchingEngines number_of_matching_engines;

    // parse method
    static SynchronizationComplete* parse(std::byte* buffer) {
        return reinterpret_cast<SynchronizationComplete*>(buffer);
    }

    // parse method const
    static const SynchronizationComplete* parse(const std::byte* buffer) {
        return reinterpret_cast<const SynchronizationComplete*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SynchronizationComplete* parse(const SesmPacketHeader* header) {
        return reinterpret_cast<const SynchronizationComplete*>(reinterpret_cast<const std::byte*>(header) + sizeof(SesmPacketHeader));
    }
};

#pragma pack(pop)
}
