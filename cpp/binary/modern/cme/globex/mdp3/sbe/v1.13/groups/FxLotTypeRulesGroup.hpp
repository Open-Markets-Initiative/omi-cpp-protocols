#pragma once

#include "../types/LotType.hpp"
#include "../types/MinLotSizeUInt64.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct FxLotTypeRulesGroup {

    LotType lot_type;
    MinLotSizeUInt64 min_lot_size_u_int_64;

    // parse method
    static FxLotTypeRulesGroup* parse(std::byte* buffer) {
        return reinterpret_cast<FxLotTypeRulesGroup*>(buffer);
    }

    // parse method const
    static const FxLotTypeRulesGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const FxLotTypeRulesGroup*>(buffer);
    }
};

#pragma pack(pop)
}
