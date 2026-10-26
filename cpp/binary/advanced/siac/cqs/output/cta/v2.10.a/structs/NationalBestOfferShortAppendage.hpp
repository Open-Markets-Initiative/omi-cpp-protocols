#pragma once

#include <cstddef>
#include "../types/BestOfferParticipantId.hpp"
#include "../types/BestOfferPriceShort.hpp"
#include "../types/BestOfferSizeShort.hpp"

namespace siac::cqs::output::cta::v2_10_a {

namespace cta_output = ::siac::cqs::output::cta::v2_10_a;

#pragma pack(push, 1)

struct national_best_offer_short_appendage {

    cta_output::best_offer_participant_id best_offer_participant_id;
    cta_output::best_offer_price_short best_offer_price_short;
    cta_output::best_offer_size_short best_offer_size_short;

    // parse method
    static national_best_offer_short_appendage* parse(std::byte* buffer) {
        return reinterpret_cast<national_best_offer_short_appendage*>(buffer);
    }

    // parse method const
    static const national_best_offer_short_appendage* parse(const std::byte* buffer) {
        return reinterpret_cast<const national_best_offer_short_appendage*>(buffer);
    }
};

// layout verification
static_assert(offsetof(national_best_offer_short_appendage, best_offer_participant_id) == 0, "unexpected offset of national_best_offer_short_appendage::best_offer_participant_id");
static_assert(offsetof(national_best_offer_short_appendage, best_offer_price_short) == 1, "unexpected offset of national_best_offer_short_appendage::best_offer_price_short");
static_assert(offsetof(national_best_offer_short_appendage, best_offer_size_short) == 3, "unexpected offset of national_best_offer_short_appendage::best_offer_size_short");
static_assert(sizeof(national_best_offer_short_appendage) == 5, "unexpected sizeof national_best_offer_short_appendage");

#pragma pack(pop)
}
