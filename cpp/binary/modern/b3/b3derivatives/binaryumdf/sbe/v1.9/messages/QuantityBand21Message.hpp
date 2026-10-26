#pragma once

#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/Offset9Padding3.hpp"
#include "../types/AvgDailyTradedQty.hpp"
#include "../types/MaxTradeVol.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

#pragma pack(push, 1)

// QuantityBand_21Message
struct QuantityBand21Message {

    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    Offset9Padding3 offset_9_padding_3;
    AvgDailyTradedQty avg_daily_traded_qty;
    MaxTradeVol max_trade_vol;
    MdEntryTimestamp md_entry_timestamp;
    RptSeq rpt_seq;

    // parse method
    static QuantityBand21Message* parse(std::byte* buffer) {
        return reinterpret_cast<QuantityBand21Message*>(buffer);
    }

    // parse method const
    static const QuantityBand21Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const QuantityBand21Message*>(buffer);
    }
};

#pragma pack(pop)
}
