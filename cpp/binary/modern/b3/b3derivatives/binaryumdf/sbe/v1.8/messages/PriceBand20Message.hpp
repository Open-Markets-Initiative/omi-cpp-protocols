#pragma once

#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/PriceBandType.hpp"
#include "../types/PriceLimitType.hpp"
#include "../types/PriceBandMidpointPriceType.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/TradingReferencePriceLegacy.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

#pragma pack(push, 1)

// PriceBand_20Message
struct PriceBand20Message {

    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    PriceBandType price_band_type;
    PriceLimitType price_limit_type;
    PriceBandMidpointPriceType price_band_midpoint_price_type;
    LowLimitPrice low_limit_price;
    HighLimitPrice high_limit_price;
    TradingReferencePriceLegacy trading_reference_price_legacy;
    MdEntryTimestamp md_entry_timestamp;
    RptSeq rpt_seq;

    // parse method
    static PriceBand20Message* parse(std::byte* buffer) {
        return reinterpret_cast<PriceBand20Message*>(buffer);
    }

    // parse method const
    static const PriceBand20Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const PriceBand20Message*>(buffer);
    }
};

#pragma pack(pop)
}
