#pragma once

#include <cstddef>
#include "../types/TrdRegTsTimePriority.hpp"
#include "../types/DisplayQty.hpp"
#include "../types/Side.hpp"
#include "../types/Pad7.hpp"
#include "../types/Price.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

namespace fbe_eobi = ::bse::bseindia::eobi::fbe::v1_4;

#pragma pack(push, 1)

struct order_details {

    fbe_eobi::trd_reg_ts_time_priority trd_reg_ts_time_priority;
    fbe_eobi::display_qty display_qty;
    fbe_eobi::side side;
    fbe_eobi::pad_7 pad_7;
    fbe_eobi::price price;

    // parse method
    static order_details* parse(std::byte* buffer) {
        return reinterpret_cast<order_details*>(buffer);
    }

    // parse method const
    static const order_details* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_details*>(buffer);
    }
};

// layout verification
static_assert(offsetof(order_details, trd_reg_ts_time_priority) == 0, "unexpected offset of order_details::trd_reg_ts_time_priority");
static_assert(offsetof(order_details, display_qty) == 8, "unexpected offset of order_details::display_qty");
static_assert(offsetof(order_details, side) == 16, "unexpected offset of order_details::side");
static_assert(offsetof(order_details, pad_7) == 17, "unexpected offset of order_details::pad_7");
static_assert(offsetof(order_details, price) == 24, "unexpected offset of order_details::price");
static_assert(sizeof(order_details) == 32, "unexpected sizeof order_details");

#pragma pack(pop)
}
