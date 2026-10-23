#pragma once

#include "../types/BestBidParticipantId.hpp"
#include "../types/BestBidQuoteCondition.hpp"
#include "../types/BestBidPriceLong.hpp"
#include "../types/BestBidSizeLong.hpp"
#include "../types/FinraBestBidMarketMakerId.hpp"

namespace siac::cqs::output::cta::v2_10_a {

#pragma pack(push, 1)

struct NationalBestBidLongAppendage {

    BestBidParticipantId best_bid_participant_id;
    BestBidQuoteCondition best_bid_quote_condition;
    BestBidPriceLong best_bid_price_long;
    BestBidSizeLong best_bid_size_long;
    FinraBestBidMarketMakerId finra_best_bid_market_maker_id;

    // parse method
    static NationalBestBidLongAppendage* parse(std::byte* buffer) {
        return reinterpret_cast<NationalBestBidLongAppendage*>(buffer);
    }

    // parse method const
    static const NationalBestBidLongAppendage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NationalBestBidLongAppendage*>(buffer);
    }
};

#pragma pack(pop)
}
