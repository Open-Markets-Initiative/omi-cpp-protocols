// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/SecurityType.hpp
#pragma once

#include "../types/SecurityTypeLength.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct SecurityType {

    SecurityTypeLength security_type_length;

    // parse method
    static SecurityType* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityType*>(buffer);
    }

    // parse method const
    static const SecurityType* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityType*>(buffer);
    }
};

#pragma pack(pop)
}
