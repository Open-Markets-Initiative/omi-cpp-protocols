#pragma once

#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/MaxPriceVariation.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct IncrementalRefreshLimitsBandingGroup {

    HighLimitPrice high_limit_price;
    LowLimitPrice low_limit_price;
    MaxPriceVariation max_price_variation;
    SecurityId security_id;
    RptSeq rpt_seq;

    // parse method
    static IncrementalRefreshLimitsBandingGroup* parse(std::byte* buffer) {
        return reinterpret_cast<IncrementalRefreshLimitsBandingGroup*>(buffer);
    }

    // parse method const
    static const IncrementalRefreshLimitsBandingGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const IncrementalRefreshLimitsBandingGroup*>(buffer);
    }
};

#pragma pack(pop)
}
