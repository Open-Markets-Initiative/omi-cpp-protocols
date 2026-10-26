#pragma once

#include <cstddef>
#include "../types/BestOfferParticipantId.hpp"
#include "../types/BestOfferDenominatorCode.hpp"
#include "../types/BestOfferPrice.hpp"
#include "../types/BestOfferSize.hpp"

namespace siac::opra::output::obi::v6_2 {

namespace obi_output = ::siac::opra::output::obi::v6_2;

#pragma pack(push, 1)

struct best_offer_appendage {

    obi_output::best_offer_participant_id best_offer_participant_id;
    obi_output::best_offer_denominator_code best_offer_denominator_code;
    obi_output::best_offer_price best_offer_price;
    obi_output::best_offer_size best_offer_size;

    // parse method
    static best_offer_appendage* parse(std::byte* buffer) {
        return reinterpret_cast<best_offer_appendage*>(buffer);
    }

    // parse method const
    static const best_offer_appendage* parse(const std::byte* buffer) {
        return reinterpret_cast<const best_offer_appendage*>(buffer);
    }
};

// layout verification
static_assert(offsetof(best_offer_appendage, best_offer_participant_id) == 0, "unexpected offset of best_offer_appendage::best_offer_participant_id");
static_assert(offsetof(best_offer_appendage, best_offer_denominator_code) == 1, "unexpected offset of best_offer_appendage::best_offer_denominator_code");
static_assert(offsetof(best_offer_appendage, best_offer_price) == 2, "unexpected offset of best_offer_appendage::best_offer_price");
static_assert(offsetof(best_offer_appendage, best_offer_size) == 6, "unexpected offset of best_offer_appendage::best_offer_size");
static_assert(sizeof(best_offer_appendage) == 10, "unexpected sizeof best_offer_appendage");

#pragma pack(pop)
}
