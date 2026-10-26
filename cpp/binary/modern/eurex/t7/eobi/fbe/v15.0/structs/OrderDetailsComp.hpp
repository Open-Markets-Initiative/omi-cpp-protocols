#pragma once

#include "../types/TrdRegTsTimePriority.hpp"
#include "../types/DisplayQty.hpp"
#include "../types/Side.hpp"
#include "../types/OrdType.hpp"
#include "../types/HhiIndicator.hpp"
#include "../types/Pad5.hpp"
#include "../types/Price.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

#pragma pack(push, 1)

struct OrderDetailsComp {

    TrdRegTsTimePriority trd_reg_ts_time_priority;
    DisplayQty display_qty;
    Side side;
    OrdType ord_type;
    HhiIndicator hhi_indicator;
    Pad5 pad5;
    Price price;

    // parse method
    static OrderDetailsComp* parse(std::byte* buffer) {
        return reinterpret_cast<OrderDetailsComp*>(buffer);
    }

    // parse method const
    static const OrderDetailsComp* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderDetailsComp*>(buffer);
    }
};

#pragma pack(pop)
}
