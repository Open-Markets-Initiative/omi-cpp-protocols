#pragma once

#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/Offset10Padding2.hpp"
#include "../types/MdFuturePrice.hpp"
#include "../types/MdEntrySizeQuantity.hpp"
#include "../types/TradeId.hpp"
#include "../types/TradeDate.hpp"
#include "../types/Offset34Padding2.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

#pragma pack(push, 1)

// TradeBust_57Message
struct TradeBust57Message {

    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    TradingSessionId trading_session_id;
    Offset10Padding2 offset_10_padding_2;
    MdFuturePrice md_future_price;
    MdEntrySizeQuantity md_entry_size_quantity;
    TradeId trade_id;
    TradeDate trade_date;
    Offset34Padding2 offset_34_padding_2;
    MdEntryTimestamp md_entry_timestamp;
    RptSeq rpt_seq;

    // parse method
    static TradeBust57Message* parse(std::byte* buffer) {
        return reinterpret_cast<TradeBust57Message*>(buffer);
    }

    // parse method const
    static const TradeBust57Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeBust57Message*>(buffer);
    }
};

#pragma pack(pop)
}
