#pragma once

#include "../types/StypeIn.hpp"
#include "../types/StypeInSymbol.hpp"
#include "../types/StypeOut.hpp"
#include "../types/StypeOutSymbol.hpp"
#include "../types/StartTs.hpp"
#include "../types/EndTs.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

#pragma pack(push, 1)

// A symbol mapping message, which maps a symbol of one SType to another
struct SymbolMappingMsg {

    StypeIn stype_in;
    StypeInSymbol stype_in_symbol;
    StypeOut stype_out;
    StypeOutSymbol stype_out_symbol;
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
