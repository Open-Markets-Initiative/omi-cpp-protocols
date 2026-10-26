#pragma once

#include "../types/UnderlyingSecurityId.hpp"
#include "../types/IndexPct.hpp"
#include "../types/IndexTheoreticalQty.hpp"
#include "../types/UnderlyingSymbol.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

#pragma pack(push, 1)

struct DeprecatedUnderlyingsGroup {

    UnderlyingSecurityId underlying_security_id;
    IndexPct index_pct;
    IndexTheoreticalQty index_theoretical_qty;
    UnderlyingSymbol underlying_symbol;

    // parse method
    static DeprecatedUnderlyingsGroup* parse(std::byte* buffer) {
        return reinterpret_cast<DeprecatedUnderlyingsGroup*>(buffer);
    }

    // parse method const
    static const DeprecatedUnderlyingsGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const DeprecatedUnderlyingsGroup*>(buffer);
    }
};

#pragma pack(pop)
}
