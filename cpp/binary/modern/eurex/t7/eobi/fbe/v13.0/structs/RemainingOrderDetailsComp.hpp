#pragma once

#include "../types/TrdRegTsPrevTimePriority.hpp"
#include "../types/DisplayQty.hpp"
#include "../types/Price.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

#pragma pack(push, 1)

struct RemainingOrderDetailsComp {

    TrdRegTsPrevTimePriority trd_reg_ts_prev_time_priority;
    DisplayQty display_qty;
    Price price;

    // parse method
    static RemainingOrderDetailsComp* parse(std::byte* buffer) {
        return reinterpret_cast<RemainingOrderDetailsComp*>(buffer);
    }

    // parse method const
    static const RemainingOrderDetailsComp* parse(const std::byte* buffer) {
        return reinterpret_cast<const RemainingOrderDetailsComp*>(buffer);
    }
};

#pragma pack(pop)
}
