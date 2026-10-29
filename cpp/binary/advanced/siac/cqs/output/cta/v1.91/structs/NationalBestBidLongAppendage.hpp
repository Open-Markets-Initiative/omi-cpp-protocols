#pragma once

#include <cstddef>
#include "../types/BestBidParticipantId.hpp"
#include "../types/BestBidQuoteCondition.hpp"
#include "../types/BestBidPriceLong.hpp"
#include "../types/BestBidSizeLong.hpp"
#include "../types/FinraBestBidMarketMakerId.hpp"

namespace siac::cqs::output::cta::v1_91 {

namespace cta_output = ::siac::cqs::output::cta::v1_91;

#pragma pack(push, 1)

struct national_best_bid_long_appendage {

    cta_output::best_bid_participant_id best_bid_participant_id;
    cta_output::best_bid_quote_condition best_bid_quote_condition;
    cta_output::best_bid_price_long best_bid_price_long;
    cta_output::best_bid_size_long best_bid_size_long;
    cta_output::finra_best_bid_market_maker_id finra_best_bid_market_maker_id;

    // parse method
    static national_best_bid_long_appendage* parse(std::byte* buffer) {
        return reinterpret_cast<national_best_bid_long_appendage*>(buffer);
    }

    // parse method const
    static const national_best_bid_long_appendage* parse(const std::byte* buffer) {
        return reinterpret_cast<const national_best_bid_long_appendage*>(buffer);
    }
};

// layout verification
static_assert(offsetof(national_best_bid_long_appendage, best_bid_participant_id) == 0, "unexpected offset of national_best_bid_long_appendage::best_bid_participant_id");
static_assert(offsetof(national_best_bid_long_appendage, best_bid_quote_condition) == 1, "unexpected offset of national_best_bid_long_appendage::best_bid_quote_condition");
static_assert(offsetof(national_best_bid_long_appendage, best_bid_price_long) == 2, "unexpected offset of national_best_bid_long_appendage::best_bid_price_long");
static_assert(offsetof(national_best_bid_long_appendage, best_bid_size_long) == 10, "unexpected offset of national_best_bid_long_appendage::best_bid_size_long");
static_assert(offsetof(national_best_bid_long_appendage, finra_best_bid_market_maker_id) == 14, "unexpected offset of national_best_bid_long_appendage::finra_best_bid_market_maker_id");
static_assert(sizeof(national_best_bid_long_appendage) == 18, "unexpected sizeof national_best_bid_long_appendage");

#pragma pack(pop)
}
