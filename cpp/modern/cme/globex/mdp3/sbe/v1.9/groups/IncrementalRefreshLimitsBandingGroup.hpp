#pragma once

#include "../types/HighLimitPriceEx.hpp"
#include "../types/LowLimitPriceEx.hpp"
#include "../types/MaxPriceVariationEx.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

struct IncrementalRefreshLimitsBandingGroup {

    HighLimitPriceEx high_limit_price_ex;
    LowLimitPriceEx low_limit_price_ex;
    MaxPriceVariationEx max_price_variation_ex;
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
