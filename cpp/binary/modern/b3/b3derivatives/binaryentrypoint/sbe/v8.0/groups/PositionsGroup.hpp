#pragma once

#include "../types/PosType.hpp"
#include "../types/LongQtyOptional.hpp"
#include "../types/ShortQty.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

struct PositionsGroup {

    PosType pos_type;
    LongQtyOptional long_qty_optional;
    ShortQty short_qty;

    // parse method
    static PositionsGroup* parse(std::byte* buffer) {
        return reinterpret_cast<PositionsGroup*>(buffer);
    }

    // parse method const
    static const PositionsGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const PositionsGroup*>(buffer);
    }
};

#pragma pack(pop)
}
