#pragma once

#include "../types/BestBidParticipantId.hpp"
#include "../types/BestBidPriceShort.hpp"
#include "../types/BestBidSizeShort.hpp"

namespace siac::cqs::output::cta::v1_91 {

#pragma pack(push, 1)

struct NationalBestBidShortAppendage {

    BestBidParticipantId best_bid_participant_id;
    BestBidPriceShort best_bid_price_short;
    BestBidSizeShort best_bid_size_short;

    // parse method
    static NationalBestBidShortAppendage* parse(std::byte* buffer) {
        return reinterpret_cast<NationalBestBidShortAppendage*>(buffer);
    }

    // parse method const
    static const NationalBestBidShortAppendage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NationalBestBidShortAppendage*>(buffer);
    }
};

#pragma pack(pop)
}
