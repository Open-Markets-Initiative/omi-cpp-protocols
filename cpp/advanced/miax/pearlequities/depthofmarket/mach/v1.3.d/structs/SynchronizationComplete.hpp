#pragma once

#include <cstddef>
#include "../types/NumberOfMatchingEngines.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

struct synchronization_complete {

    mach_depthofmarket::number_of_matching_engines number_of_matching_engines;

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
static_assert(offsetof(synchronization_complete, number_of_matching_engines) == 0, "unexpected offset of synchronization_complete::number_of_matching_engines");
static_assert(sizeof(synchronization_complete) == 1, "unexpected sizeof synchronization_complete");

#pragma pack(pop)
}
