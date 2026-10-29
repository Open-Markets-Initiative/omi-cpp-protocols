#pragma once

#include "../types/CompactOfferPrice.hpp"
#include "../types/CompactOfferSize.hpp"
#include "../types/Reserved2.hpp"
#include "../types/OfferCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

#pragma pack(push, 1)

struct CompactOffer {

    CompactOfferPrice compact_offer_price;
    CompactOfferSize compact_offer_size;
    Reserved2 reserved_2;
    OfferCondition offer_condition;

    // parse method
    static CompactOffer* parse(std::byte* buffer) {
        return reinterpret_cast<CompactOffer*>(buffer);
    }

    // parse method const
    static const CompactOffer* parse(const std::byte* buffer) {
        return reinterpret_cast<const CompactOffer*>(buffer);
    }
};

#pragma pack(pop)
}
