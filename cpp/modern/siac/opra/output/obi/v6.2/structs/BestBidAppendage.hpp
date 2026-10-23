#pragma once

#include "../types/BestBidParticipantId.hpp"
#include "../types/BestBidDenominatorCode.hpp"
#include "../types/BestBidPrice.hpp"
#include "../types/BestBidSize.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

struct BestBidAppendage {

    BestBidParticipantId best_bid_participant_id;
    BestBidDenominatorCode best_bid_denominator_code;
    BestBidPrice best_bid_price;
    BestBidSize best_bid_size;

    // parse method
    static BestBidAppendage* parse(std::byte* buffer) {
        return reinterpret_cast<BestBidAppendage*>(buffer);
    }

    // parse method const
    static const BestBidAppendage* parse(const std::byte* buffer) {
        return reinterpret_cast<const BestBidAppendage*>(buffer);
    }
};

#pragma pack(pop)
}
