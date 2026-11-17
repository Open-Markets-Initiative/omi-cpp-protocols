// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: structs/WideBid.hpp
#pragma once

#include <cstddef>
#include "../types/WideBidPrice.hpp"
#include "../types/WideBidSize.hpp"
#include "../types/Reserved4.hpp"
#include "../types/BidCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

namespace mach_complextopofmarket = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

#pragma pack(push, 1)

struct wide_bid {

    mach_complextopofmarket::wide_bid_price wide_bid_price;
    mach_complextopofmarket::wide_bid_size wide_bid_size;
    mach_complextopofmarket::reserved_4 reserved_4;
    mach_complextopofmarket::bid_condition bid_condition;

    // parse method
    static wide_bid* parse(std::byte* buffer) {
        return reinterpret_cast<wide_bid*>(buffer);
    }

    // parse method const
    static const wide_bid* parse(const std::byte* buffer) {
        return reinterpret_cast<const wide_bid*>(buffer);
    }
};

// layout verification
static_assert(offsetof(wide_bid, wide_bid_price) == 0, "unexpected offset of wide_bid::wide_bid_price");
static_assert(offsetof(wide_bid, wide_bid_size) == 8, "unexpected offset of wide_bid::wide_bid_size");
static_assert(offsetof(wide_bid, reserved_4) == 12, "unexpected offset of wide_bid::reserved_4");
static_assert(offsetof(wide_bid, bid_condition) == 16, "unexpected offset of wide_bid::bid_condition");
static_assert(sizeof(wide_bid) == 17, "unexpected sizeof wide_bid");

#pragma pack(pop)
}
