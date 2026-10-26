#pragma once

#include "../types/BestBidParticipantId.hpp"
#include "../types/BestBidQuoteCondition.hpp"
#include "../types/BestBidPriceLong.hpp"
#include "../types/BestBidSizeLong.hpp"
#include "../types/FinraBestBidMarketMakerId.hpp"
#include "../types/BestOfferParticipantId.hpp"
#include "../types/BestOfferQuoteCondition.hpp"
#include "../types/BestOfferPriceLong.hpp"
#include "../types/BestOfferSizeLong.hpp"
#include "../types/FinraBestOfferMarketMakerId.hpp"

namespace siac::cqs::output::cta::v2_10_a {

#pragma pack(push, 1)

struct NationalBestBidAndOfferLongAppendage {

    BestBidParticipantId best_bid_participant_id;
    BestBidQuoteCondition best_bid_quote_condition;
    BestBidPriceLong best_bid_price_long;
    BestBidSizeLong best_bid_size_long;
    FinraBestBidMarketMakerId finra_best_bid_market_maker_id;
    BestOfferParticipantId best_offer_participant_id;
    BestOfferQuoteCondition best_offer_quote_condition;
    BestOfferPriceLong best_offer_price_long;
    BestOfferSizeLong best_offer_size_long;
    FinraBestOfferMarketMakerId finra_best_offer_market_maker_id;

    // parse method
    static NationalBestBidAndOfferLongAppendage* parse(std::byte* buffer) {
        return reinterpret_cast<NationalBestBidAndOfferLongAppendage*>(buffer);
    }

    // parse method const
    static const NationalBestBidAndOfferLongAppendage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NationalBestBidAndOfferLongAppendage*>(buffer);
    }
};

#pragma pack(pop)
}
