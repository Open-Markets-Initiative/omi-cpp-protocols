// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/UnderlyingSymbol.hpp
#pragma once

#include "../types/UnderlyingSymbolLength.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct UnderlyingSymbol {

    UnderlyingSymbolLength underlying_symbol_length;

    // parse method
    static UnderlyingSymbol* parse(std::byte* buffer) {
        return reinterpret_cast<UnderlyingSymbol*>(buffer);
    }

    // parse method const
    static const UnderlyingSymbol* parse(const std::byte* buffer) {
        return reinterpret_cast<const UnderlyingSymbol*>(buffer);
    }
};

#pragma pack(pop)
}
