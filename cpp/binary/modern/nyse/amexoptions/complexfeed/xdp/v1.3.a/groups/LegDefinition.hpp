#pragma once

#include "../types/SymbolIndex.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/Side.hpp"
#include "../types/LegSecurityType.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

#pragma pack(push, 1)

struct LegDefinition {

    SymbolIndex symbol_index;
    LegRatioQty leg_ratio_qty;
    Side side;
    LegSecurityType leg_security_type;

    // parse method
    static LegDefinition* parse(std::byte* buffer) {
        return reinterpret_cast<LegDefinition*>(buffer);
    }

    // parse method const
    static const LegDefinition* parse(const std::byte* buffer) {
        return reinterpret_cast<const LegDefinition*>(buffer);
    }
};

#pragma pack(pop)
}
