#pragma once

#include "../types/BestOfferParticipantId.hpp"
#include "../types/BestOfferQuoteCondition.hpp"
#include "../types/BestOfferPriceLong.hpp"
#include "../types/BestOfferSizeLong.hpp"
#include "../types/FinraBestOfferMarketMakerId.hpp"

namespace siac::cqs::output::cta::v1_91 {

#pragma pack(push, 1)

struct NationalBestOfferLongAppendage {

    BestOfferParticipantId best_offer_participant_id;
    BestOfferQuoteCondition best_offer_quote_condition;
    BestOfferPriceLong best_offer_price_long;
    BestOfferSizeLong best_offer_size_long;
    FinraBestOfferMarketMakerId finra_best_offer_market_maker_id;

    // parse method
    static NationalBestOfferLongAppendage* parse(std::byte* buffer) {
        return reinterpret_cast<NationalBestOfferLongAppendage*>(buffer);
    }

    // parse method const
    static const NationalBestOfferLongAppendage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NationalBestOfferLongAppendage*>(buffer);
    }
};

#pragma pack(pop)
}
