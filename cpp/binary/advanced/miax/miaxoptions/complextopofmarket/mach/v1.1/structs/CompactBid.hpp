// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: structs/CompactBid.hpp
#pragma once

#include <cstddef>
#include "../types/CompactBidPrice.hpp"
#include "../types/CompactBidSize.hpp"
#include "../types/Reserved2.hpp"
#include "../types/BidCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

namespace mach_complextopofmarket = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

#pragma pack(push, 1)

struct compact_bid {

    mach_complextopofmarket::compact_bid_price compact_bid_price;
    mach_complextopofmarket::compact_bid_size compact_bid_size;
    mach_complextopofmarket::reserved_2 reserved_2;
    mach_complextopofmarket::bid_condition bid_condition;

    // parse method
    static compact_bid* parse(std::byte* buffer) {
        return reinterpret_cast<compact_bid*>(buffer);
    }

    // parse method const
    static const compact_bid* parse(const std::byte* buffer) {
        return reinterpret_cast<const compact_bid*>(buffer);
    }
};

// layout verification
static_assert(offsetof(compact_bid, compact_bid_price) == 0, "unexpected offset of compact_bid::compact_bid_price");
static_assert(offsetof(compact_bid, compact_bid_size) == 2, "unexpected offset of compact_bid::compact_bid_size");
static_assert(offsetof(compact_bid, reserved_2) == 4, "unexpected offset of compact_bid::reserved_2");
static_assert(offsetof(compact_bid, bid_condition) == 6, "unexpected offset of compact_bid::bid_condition");
static_assert(sizeof(compact_bid) == 7, "unexpected sizeof compact_bid");

#pragma pack(pop)
}
