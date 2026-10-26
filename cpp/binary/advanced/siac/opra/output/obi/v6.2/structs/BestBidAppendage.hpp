#pragma once

#include <cstddef>
#include "../types/BestBidParticipantId.hpp"
#include "../types/BestBidDenominatorCode.hpp"
#include "../types/BestBidPrice.hpp"
#include "../types/BestBidSize.hpp"

namespace siac::opra::output::obi::v6_2 {

namespace obi_output = ::siac::opra::output::obi::v6_2;

#pragma pack(push, 1)

struct best_bid_appendage {

    obi_output::best_bid_participant_id best_bid_participant_id;
    obi_output::best_bid_denominator_code best_bid_denominator_code;
    obi_output::best_bid_price best_bid_price;
    obi_output::best_bid_size best_bid_size;

    // parse method
    static best_bid_appendage* parse(std::byte* buffer) {
        return reinterpret_cast<best_bid_appendage*>(buffer);
    }

    // parse method const
    static const best_bid_appendage* parse(const std::byte* buffer) {
        return reinterpret_cast<const best_bid_appendage*>(buffer);
    }
};

// layout verification
static_assert(offsetof(best_bid_appendage, best_bid_participant_id) == 0, "unexpected offset of best_bid_appendage::best_bid_participant_id");
static_assert(offsetof(best_bid_appendage, best_bid_denominator_code) == 1, "unexpected offset of best_bid_appendage::best_bid_denominator_code");
static_assert(offsetof(best_bid_appendage, best_bid_price) == 2, "unexpected offset of best_bid_appendage::best_bid_price");
static_assert(offsetof(best_bid_appendage, best_bid_size) == 6, "unexpected offset of best_bid_appendage::best_bid_size");
static_assert(sizeof(best_bid_appendage) == 10, "unexpected sizeof best_bid_appendage");

#pragma pack(pop)
}
