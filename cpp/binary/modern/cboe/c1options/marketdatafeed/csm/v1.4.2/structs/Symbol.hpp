// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/Symbol.hpp
#pragma once

#include "../types/SymbolLength.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct Symbol {

    SymbolLength symbol_length;

    // parse method
    static Symbol* parse(std::byte* buffer) {
        return reinterpret_cast<Symbol*>(buffer);
    }

    // parse method const
    static const Symbol* parse(const std::byte* buffer) {
        return reinterpret_cast<const Symbol*>(buffer);
    }
};

#pragma pack(pop)
}
