#pragma once

#include "../types/LotType.hpp"
#include "../types/MinLotSizeDecimalQty.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct LotTypeRulesGroup {

    LotType lot_type;
    MinLotSizeDecimalQty min_lot_size_decimal_qty;

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
