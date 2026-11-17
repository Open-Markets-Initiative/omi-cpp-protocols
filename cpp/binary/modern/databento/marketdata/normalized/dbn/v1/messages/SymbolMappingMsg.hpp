// Databento.MarketData.Normalized.Dbn.v1: messages/SymbolMappingMsg.hpp
#pragma once

#include "../types/StypeInSymbol.hpp"
#include "../types/StypeOutSymbol.hpp"
#include "../types/Dummy4.hpp"
#include "../types/StartTs.hpp"
#include "../types/EndTs.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

#pragma pack(push, 1)

// A symbol mapping message, which maps a symbol of one SType to another
struct SymbolMappingMsg {

    StypeInSymbol stype_in_symbol;
    StypeOutSymbol stype_out_symbol;
    Dummy4 dummy_4;
    StartTs start_ts;
    EndTs end_ts;

    // parse method
    static SymbolMappingMsg* parse(std::byte* buffer) {
        return reinterpret_cast<SymbolMappingMsg*>(buffer);
    }

    // parse method const
    static const SymbolMappingMsg* parse(const std::byte* buffer) {
        return reinterpret_cast<const SymbolMappingMsg*>(buffer);
    }
};

#pragma pack(pop)
}
