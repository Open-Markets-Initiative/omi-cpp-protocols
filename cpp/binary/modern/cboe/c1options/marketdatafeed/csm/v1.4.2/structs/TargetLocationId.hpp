// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/TargetLocationId.hpp
#pragma once

#include "../types/TargetLocationIdLength.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct TargetLocationId {

    TargetLocationIdLength target_location_id_length;

    // parse method
    static TargetLocationId* parse(std::byte* buffer) {
        return reinterpret_cast<TargetLocationId*>(buffer);
    }

    // parse method const
    static const TargetLocationId* parse(const std::byte* buffer) {
        return reinterpret_cast<const TargetLocationId*>(buffer);
    }
};

#pragma pack(pop)
}
