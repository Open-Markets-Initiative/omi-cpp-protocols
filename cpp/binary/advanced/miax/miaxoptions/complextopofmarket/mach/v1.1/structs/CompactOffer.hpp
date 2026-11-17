// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: structs/CompactOffer.hpp
#pragma once

#include <cstddef>
#include "../types/CompactOfferPrice.hpp"
#include "../types/CompactOfferSize.hpp"
#include "../types/Reserved2.hpp"
#include "../types/OfferCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

namespace mach_complextopofmarket = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

#pragma pack(push, 1)

struct compact_offer {

    mach_complextopofmarket::compact_offer_price compact_offer_price;
    mach_complextopofmarket::compact_offer_size compact_offer_size;
    mach_complextopofmarket::reserved_2 reserved_2;
    mach_complextopofmarket::offer_condition offer_condition;

    // parse method
    static compact_offer* parse(std::byte* buffer) {
        return reinterpret_cast<compact_offer*>(buffer);
    }

    // parse method const
    static const compact_offer* parse(const std::byte* buffer) {
        return reinterpret_cast<const compact_offer*>(buffer);
    }
};

// layout verification
static_assert(offsetof(compact_offer, compact_offer_price) == 0, "unexpected offset of compact_offer::compact_offer_price");
static_assert(offsetof(compact_offer, compact_offer_size) == 2, "unexpected offset of compact_offer::compact_offer_size");
static_assert(offsetof(compact_offer, reserved_2) == 4, "unexpected offset of compact_offer::reserved_2");
static_assert(offsetof(compact_offer, offer_condition) == 6, "unexpected offset of compact_offer::offer_condition");
static_assert(sizeof(compact_offer) == 7, "unexpected sizeof compact_offer");

#pragma pack(pop)
}
