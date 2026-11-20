// Cme.Globex.Mdp3.Sbe.v1.9: groups/IncrementalRefreshLimitsBandingLegacyGroup.hpp
#pragma once

#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/MaxPriceVariation.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

struct IncrementalRefreshLimitsBandingLegacyGroup {

    HighLimitPrice high_limit_price;
    LowLimitPrice low_limit_price;
    MaxPriceVariation max_price_variation;
    SecurityId security_id;
    RptSeq rpt_seq;

    // parse method
    static IncrementalRefreshLimitsBandingLegacyGroup* parse(std::byte* buffer) {
        return reinterpret_cast<IncrementalRefreshLimitsBandingLegacyGroup*>(buffer);
    }

    // parse method const
    static const IncrementalRefreshLimitsBandingLegacyGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const IncrementalRefreshLimitsBandingLegacyGroup*>(buffer);
    }
};

#pragma pack(pop)
}
