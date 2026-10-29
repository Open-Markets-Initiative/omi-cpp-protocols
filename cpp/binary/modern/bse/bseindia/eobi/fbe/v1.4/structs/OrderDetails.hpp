#pragma once

#include "../types/TrdRegTsTimePriority.hpp"
#include "../types/DisplayQty.hpp"
#include "../types/Side.hpp"
#include "../types/Pad7.hpp"
#include "../types/Price.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

struct OrderDetails {

    TrdRegTsTimePriority trd_reg_ts_time_priority;
    DisplayQty display_qty;
    Side side;
    Pad7 pad_7;
    Price price;

    // parse method
    static OrderDetails* parse(std::byte* buffer) {
        return reinterpret_cast<OrderDetails*>(buffer);
    }

    // parse method const
    static const OrderDetails* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderDetails*>(buffer);
    }
};

#pragma pack(pop)
}
