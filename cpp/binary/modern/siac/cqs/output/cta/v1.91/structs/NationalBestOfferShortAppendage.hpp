#pragma once

#include "../types/BestOfferParticipantId.hpp"
#include "../types/BestOfferPriceShort.hpp"
#include "../types/BestOfferSizeShort.hpp"

namespace siac::cqs::output::cta::v1_91 {

#pragma pack(push, 1)

struct NationalBestOfferShortAppendage {

    BestOfferParticipantId best_offer_participant_id;
    BestOfferPriceShort best_offer_price_short;
    BestOfferSizeShort best_offer_size_short;

    // parse method
    static NationalBestOfferShortAppendage* parse(std::byte* buffer) {
        return reinterpret_cast<NationalBestOfferShortAppendage*>(buffer);
    }

    // parse method const
    static const NationalBestOfferShortAppendage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NationalBestOfferShortAppendage*>(buffer);
    }
};

#pragma pack(pop)
}
