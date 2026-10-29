#pragma once

#include "../types/WideBidPrice.hpp"
#include "../types/WideBidSize.hpp"
#include "../types/Reserved4.hpp"
#include "../types/BidCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

#pragma pack(push, 1)

struct WideBid {

    WideBidPrice wide_bid_price;
    WideBidSize wide_bid_size;
    Reserved4 reserved_4;
    BidCondition bid_condition;

    // parse method
    static WideBid* parse(std::byte* buffer) {
        return reinterpret_cast<WideBid*>(buffer);
    }

    // parse method const
    static const WideBid* parse(const std::byte* buffer) {
        return reinterpret_cast<const WideBid*>(buffer);
    }
};

#pragma pack(pop)
}
