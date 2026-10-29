#pragma once

#include "../types/CompactBidPrice.hpp"
#include "../types/CompactBidSize.hpp"
#include "../types/Reserved2.hpp"
#include "../types/BidCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

#pragma pack(push, 1)

struct CompactBid {

    CompactBidPrice compact_bid_price;
    CompactBidSize compact_bid_size;
    Reserved2 reserved_2;
    BidCondition bid_condition;

    // parse method
    static CompactBid* parse(std::byte* buffer) {
        return reinterpret_cast<CompactBid*>(buffer);
    }

    // parse method const
    static const CompactBid* parse(const std::byte* buffer) {
        return reinterpret_cast<const CompactBid*>(buffer);
    }
};

#pragma pack(pop)
}
