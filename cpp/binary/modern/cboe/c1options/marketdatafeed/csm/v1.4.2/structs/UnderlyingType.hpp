// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/UnderlyingType.hpp
#pragma once

#include "../types/UnderlyingTypeLength.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct UnderlyingType {

    UnderlyingTypeLength underlying_type_length;

    // parse method
    static UnderlyingType* parse(std::byte* buffer) {
        return reinterpret_cast<UnderlyingType*>(buffer);
    }

    // parse method const
    static const UnderlyingType* parse(const std::byte* buffer) {
        return reinterpret_cast<const UnderlyingType*>(buffer);
    }
};

#pragma pack(pop)
}
