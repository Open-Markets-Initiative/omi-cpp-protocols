#pragma once

#include "../types/BestBidParticipantId.hpp"
#include "../types/BestBidDenominatorCode.hpp"
#include "../types/BestBidPrice.hpp"
#include "../types/BestBidSize.hpp"
#include "../types/BestOfferParticipantId.hpp"
#include "../types/BestOfferDenominatorCode.hpp"
#include "../types/BestOfferPrice.hpp"
#include "../types/BestOfferSize.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

struct BestBidAndOfferAppendage {

    BestBidParticipantId best_bid_participant_id;
    BestBidDenominatorCode best_bid_denominator_code;
    BestBidPrice best_bid_price;
    BestBidSize best_bid_size;
    BestOfferParticipantId best_offer_participant_id;
    BestOfferDenominatorCode best_offer_denominator_code;
    BestOfferPrice best_offer_price;
    BestOfferSize best_offer_size;

    // parse method
    static BestBidAndOfferAppendage* parse(std::byte* buffer) {
        return reinterpret_cast<BestBidAndOfferAppendage*>(buffer);
    }

    // parse method const
    static const BestBidAndOfferAppendage* parse(const std::byte* buffer) {
        return reinterpret_cast<const BestBidAndOfferAppendage*>(buffer);
    }
};

#pragma pack(pop)
}
