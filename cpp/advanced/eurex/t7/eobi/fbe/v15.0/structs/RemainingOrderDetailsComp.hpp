#pragma once

#include <cstddef>
#include "../types/TrdRegTsPrevTimePriority.hpp"
#include "../types/DisplayQty.hpp"
#include "../types/Price.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v15_0;

#pragma pack(push, 1)

struct remaining_order_details_comp {

    fbe_eobi::trd_reg_ts_prev_time_priority trd_reg_ts_prev_time_priority;
    fbe_eobi::display_qty display_qty;
    fbe_eobi::price price;

    // parse method
    static remaining_order_details_comp* parse(std::byte* buffer) {
        return reinterpret_cast<remaining_order_details_comp*>(buffer);
    }

    // parse method const
    static const remaining_order_details_comp* parse(const std::byte* buffer) {
        return reinterpret_cast<const remaining_order_details_comp*>(buffer);
    }
};

// layout verification
static_assert(offsetof(remaining_order_details_comp, trd_reg_ts_prev_time_priority) == 0, "unexpected offset of remaining_order_details_comp::trd_reg_ts_prev_time_priority");
static_assert(offsetof(remaining_order_details_comp, display_qty) == 8, "unexpected offset of remaining_order_details_comp::display_qty");
static_assert(offsetof(remaining_order_details_comp, price) == 16, "unexpected offset of remaining_order_details_comp::price");
static_assert(sizeof(remaining_order_details_comp) == 24, "unexpected sizeof remaining_order_details_comp");

#pragma pack(pop)
}
