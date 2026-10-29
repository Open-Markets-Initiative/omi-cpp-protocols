#pragma once

#include "../types/WideOfferPrice.hpp"
#include "../types/WideOfferSize.hpp"
#include "../types/Reserved4.hpp"
#include "../types/OfferCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

#pragma pack(push, 1)

struct WideOffer {

    WideOfferPrice wide_offer_price;
    WideOfferSize wide_offer_size;
    Reserved4 reserved_4;
    OfferCondition offer_condition;

    // parse method
    static WideOffer* parse(std::byte* buffer) {
        return reinterpret_cast<WideOffer*>(buffer);
    }

    // parse method const
    static const WideOffer* parse(const std::byte* buffer) {
        return reinterpret_cast<const WideOffer*>(buffer);
    }
};

#pragma pack(pop)
}
