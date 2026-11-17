// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: structs/WideOffer.hpp
#pragma once

#include <cstddef>
#include "../types/WideOfferPrice.hpp"
#include "../types/WideOfferSize.hpp"
#include "../types/Reserved4.hpp"
#include "../types/OfferCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

namespace mach_complextopofmarket = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

#pragma pack(push, 1)

struct wide_offer {

    mach_complextopofmarket::wide_offer_price wide_offer_price;
    mach_complextopofmarket::wide_offer_size wide_offer_size;
    mach_complextopofmarket::reserved_4 reserved_4;
    mach_complextopofmarket::offer_condition offer_condition;

    // parse method
    static wide_offer* parse(std::byte* buffer) {
        return reinterpret_cast<wide_offer*>(buffer);
    }

    // parse method const
    static const wide_offer* parse(const std::byte* buffer) {
        return reinterpret_cast<const wide_offer*>(buffer);
    }
};

// layout verification
static_assert(offsetof(wide_offer, wide_offer_price) == 0, "unexpected offset of wide_offer::wide_offer_price");
static_assert(offsetof(wide_offer, wide_offer_size) == 8, "unexpected offset of wide_offer::wide_offer_size");
static_assert(offsetof(wide_offer, reserved_4) == 12, "unexpected offset of wide_offer::reserved_4");
static_assert(offsetof(wide_offer, offer_condition) == 16, "unexpected offset of wide_offer::offer_condition");
static_assert(sizeof(wide_offer) == 17, "unexpected sizeof wide_offer");

#pragma pack(pop)
}
