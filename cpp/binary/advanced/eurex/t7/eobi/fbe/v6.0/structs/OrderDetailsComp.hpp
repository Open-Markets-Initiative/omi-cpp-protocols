#pragma once

#include <cstddef>
#include "../types/TrdRegTsTimePriority.hpp"
#include "../types/DisplayQty.hpp"
#include "../types/Side.hpp"
#include "../types/OrdType.hpp"
#include "../types/Pad2.hpp"
#include "../types/Price.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v6_0;

#pragma pack(push, 1)

struct order_details_comp {

    fbe_eobi::trd_reg_ts_time_priority trd_reg_ts_time_priority;
    fbe_eobi::display_qty display_qty;
    fbe_eobi::side side;
    fbe_eobi::ord_type ord_type;
    fbe_eobi::pad2 pad2;
    fbe_eobi::price price;

    // parse method
    static order_details_comp* parse(std::byte* buffer) {
        return reinterpret_cast<order_details_comp*>(buffer);
    }

    // parse method const
    static const order_details_comp* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_details_comp*>(buffer);
    }
};

// layout verification
static_assert(offsetof(order_details_comp, trd_reg_ts_time_priority) == 0, "unexpected offset of order_details_comp::trd_reg_ts_time_priority");
static_assert(offsetof(order_details_comp, display_qty) == 8, "unexpected offset of order_details_comp::display_qty");
static_assert(offsetof(order_details_comp, side) == 12, "unexpected offset of order_details_comp::side");
static_assert(offsetof(order_details_comp, ord_type) == 13, "unexpected offset of order_details_comp::ord_type");
static_assert(offsetof(order_details_comp, pad2) == 14, "unexpected offset of order_details_comp::pad2");
static_assert(offsetof(order_details_comp, price) == 16, "unexpected offset of order_details_comp::price");
static_assert(sizeof(order_details_comp) == 24, "unexpected sizeof order_details_comp");

#pragma pack(pop)
}
