#pragma once

#include "../types/SecurityId.hpp"

namespace cme::mdp3::v8 {

#pragma pack(push, 1)

struct MarketDataRequestRelatedSymbolGroup {

    SecurityId security_id;

    // parse method
    static MarketDataRequestRelatedSymbolGroup* parse(std::byte* buffer) {
        return reinterpret_cast<MarketDataRequestRelatedSymbolGroup*>(buffer);
    }

    // parse method const
    static const MarketDataRequestRelatedSymbolGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const MarketDataRequestRelatedSymbolGroup*>(buffer);
    }
};

#pragma pack(pop)
}
