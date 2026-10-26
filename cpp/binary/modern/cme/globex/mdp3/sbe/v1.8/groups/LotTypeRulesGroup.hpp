#pragma once

#include "../types/LotType.hpp"
#include "../types/MinLotSize.hpp"

namespace cme::mdp3::v8 {

#pragma pack(push, 1)

struct LotTypeRulesGroup {

    LotType lot_type;
    MinLotSize min_lot_size;

    // parse method
    static LotTypeRulesGroup* parse(std::byte* buffer) {
        return reinterpret_cast<LotTypeRulesGroup*>(buffer);
    }

    // parse method const
    static const LotTypeRulesGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const LotTypeRulesGroup*>(buffer);
    }
};

#pragma pack(pop)
}
