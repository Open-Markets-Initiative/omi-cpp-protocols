// Databento.MarketData.Normalized.Dbn.v1: structs/SymbolMapping.hpp
#pragma once

#include "../types/RawSymbolIn.hpp"
#include "../types/IntervalCount.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

#pragma pack(push, 1)

struct SymbolMapping {

    RawSymbolIn raw_symbol_in;
    IntervalCount interval_count;

    // parse method
    static SymbolMapping* parse(std::byte* buffer) {
        return reinterpret_cast<SymbolMapping*>(buffer);
    }

    // parse method const
    static const SymbolMapping* parse(const std::byte* buffer) {
        return reinterpret_cast<const SymbolMapping*>(buffer);
    }
};

#pragma pack(pop)
}
