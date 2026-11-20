// Cme.Globex.Mdp3.Sbe.v1.13: groups/FxLotTypeRulesGroup.hpp
#pragma once

#include "../types/LotType.hpp"
#include "../types/FxMinLotSize.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct FxLotTypeRulesGroup {

    LotType lot_type;
    FxMinLotSize fx_min_lot_size;

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
