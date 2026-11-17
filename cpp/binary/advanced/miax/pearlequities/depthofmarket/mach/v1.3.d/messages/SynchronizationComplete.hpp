// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/SynchronizationComplete.hpp
#pragma once

#include <cstddef>
#include "../structs/EsesmPacketHeader.hpp"
#include "../types/MatchingEngineId.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

// Synchronization Complete
struct synchronization_complete {

    struct fields_type {
        mach_depthofmarket::matching_engine_id matching_engine_id;
    };

    mach_depthofmarket::esesm_packet_header header = {std::uint16_t(sizeof(mach_depthofmarket::esesm_packet_header) + sizeof(fields_type) - 2), esesm_packet_type::enum_type::synchronization_complete};

    fields_type fields;

    // parse method
    static synchronization_complete* parse(std::byte* buffer) {
        return reinterpret_cast<synchronization_complete*>(buffer);
    }

    // parse method const
    static const synchronization_complete* parse(const std::byte* buffer) {
        return reinterpret_cast<const synchronization_complete*>(buffer);
    }

};

// layout verification
static_assert(offsetof(synchronization_complete::fields_type, matching_engine_id) == 0, "unexpected offset of synchronization_complete::fields_type::matching_engine_id");
static_assert(sizeof(synchronization_complete::fields_type) == 1, "unexpected sizeof synchronization_complete::fields_type");
static_assert(sizeof(synchronization_complete) == sizeof(mach_depthofmarket::esesm_packet_header) + 1, "unexpected sizeof synchronization_complete");

#pragma pack(pop)
}
