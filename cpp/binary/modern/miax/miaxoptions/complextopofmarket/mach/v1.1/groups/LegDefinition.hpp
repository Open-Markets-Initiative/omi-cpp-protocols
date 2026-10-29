#pragma once

#include "../types/ProductId.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/LegSide.hpp"
#include "../types/Reserved8.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

#pragma pack(push, 1)

struct LegDefinition {

    ProductId product_id;
    LegRatioQty leg_ratio_qty;
    LegSide leg_side;
    Reserved8 reserved_8;

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
