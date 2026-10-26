#pragma once

#include <cstddef>
#include "../types/BestBidParticipantId.hpp"
#include "../types/BestBidDenominatorCode.hpp"
#include "../types/BestBidPrice.hpp"
#include "../types/BestBidSize.hpp"
#include "../types/BestOfferParticipantId.hpp"
#include "../types/BestOfferDenominatorCode.hpp"
#include "../types/BestOfferPrice.hpp"
#include "../types/BestOfferSize.hpp"

namespace siac::opra::output::obi::v6_2 {

namespace obi_output = ::siac::opra::output::obi::v6_2;

#pragma pack(push, 1)

struct best_bid_and_offer_appendage {

    obi_output::best_bid_participant_id best_bid_participant_id;
    obi_output::best_bid_denominator_code best_bid_denominator_code;
    obi_output::best_bid_price best_bid_price;
    obi_output::best_bid_size best_bid_size;
    obi_output::best_offer_participant_id best_offer_participant_id;
    obi_output::best_offer_denominator_code best_offer_denominator_code;
    obi_output::best_offer_price best_offer_price;
    obi_output::best_offer_size best_offer_size;

    // parse method
    static best_bid_and_offer_appendage* parse(std::byte* buffer) {
        return reinterpret_cast<best_bid_and_offer_appendage*>(buffer);
    }

    // parse method const
    static const best_bid_and_offer_appendage* parse(const std::byte* buffer) {
        return reinterpret_cast<const best_bid_and_offer_appendage*>(buffer);
    }
};

// layout verification
static_assert(offsetof(best_bid_and_offer_appendage, best_bid_participant_id) == 0, "unexpected offset of best_bid_and_offer_appendage::best_bid_participant_id");
static_assert(offsetof(best_bid_and_offer_appendage, best_bid_denominator_code) == 1, "unexpected offset of best_bid_and_offer_appendage::best_bid_denominator_code");
static_assert(offsetof(best_bid_and_offer_appendage, best_bid_price) == 2, "unexpected offset of best_bid_and_offer_appendage::best_bid_price");
static_assert(offsetof(best_bid_and_offer_appendage, best_bid_size) == 6, "unexpected offset of best_bid_and_offer_appendage::best_bid_size");
static_assert(offsetof(best_bid_and_offer_appendage, best_offer_participant_id) == 10, "unexpected offset of best_bid_and_offer_appendage::best_offer_participant_id");
static_assert(offsetof(best_bid_and_offer_appendage, best_offer_denominator_code) == 11, "unexpected offset of best_bid_and_offer_appendage::best_offer_denominator_code");
static_assert(offsetof(best_bid_and_offer_appendage, best_offer_price) == 12, "unexpected offset of best_bid_and_offer_appendage::best_offer_price");
static_assert(offsetof(best_bid_and_offer_appendage, best_offer_size) == 16, "unexpected offset of best_bid_and_offer_appendage::best_offer_size");
static_assert(sizeof(best_bid_and_offer_appendage) == 20, "unexpected sizeof best_bid_and_offer_appendage");

#pragma pack(pop)
}
