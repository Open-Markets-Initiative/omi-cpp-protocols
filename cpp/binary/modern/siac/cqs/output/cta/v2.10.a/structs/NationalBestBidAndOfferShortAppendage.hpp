#pragma once

#include "../types/BestBidParticipantId.hpp"
#include "../types/BestBidPriceShort.hpp"
#include "../types/BestBidSizeShort.hpp"
#include "../types/BestOfferParticipantId.hpp"
#include "../types/BestOfferPriceShort.hpp"
#include "../types/BestOfferSizeShort.hpp"

namespace siac::cqs::output::cta::v2_10_a {

#pragma pack(push, 1)

struct NationalBestBidAndOfferShortAppendage {

    BestBidParticipantId best_bid_participant_id;
    BestBidPriceShort best_bid_price_short;
    BestBidSizeShort best_bid_size_short;
    BestOfferParticipantId best_offer_participant_id;
    BestOfferPriceShort best_offer_price_short;
    BestOfferSizeShort best_offer_size_short;

    // parse method
    static NationalBestBidAndOfferShortAppendage* parse(std::byte* buffer) {
        return reinterpret_cast<NationalBestBidAndOfferShortAppendage*>(buffer);
    }

    // parse method const
    static const NationalBestBidAndOfferShortAppendage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NationalBestBidAndOfferShortAppendage*>(buffer);
    }
};

#pragma pack(pop)
}
