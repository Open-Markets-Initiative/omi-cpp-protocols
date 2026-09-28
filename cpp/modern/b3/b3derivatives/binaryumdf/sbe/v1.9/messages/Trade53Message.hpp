#pragma once

#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/TradingSessionId.hpp"
#include "../bitfields/TradeCondition.hpp"
#include "../types/MdFuturePrice.hpp"
#include "../types/MdEntrySizeQuantity.hpp"
#include "../types/TradeId.hpp"
#include "../types/MdEntryBuyer.hpp"
#include "../types/MdEntrySeller.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TrdSubType.hpp"
#include "../types/Offset43Padding1.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

#pragma pack(push, 1)

// Trade_53Message
struct Trade53Message {

    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    TradingSessionId trading_session_id;
    TradeCondition trade_condition;
    MdFuturePrice md_future_price;
    MdEntrySizeQuantity md_entry_size_quantity;
    TradeId trade_id;
    MdEntryBuyer md_entry_buyer;
    MdEntrySeller md_entry_seller;
    TradeDate trade_date;
    TrdSubType trd_sub_type;
    Offset43Padding1 offset_43_padding_1;
    MdEntryTimestamp md_entry_timestamp;
    RptSeq rpt_seq;

    // parse method
    static Trade53Message* parse(std::byte* buffer) {
        return reinterpret_cast<Trade53Message*>(buffer);
    }

    // parse method const
    static const Trade53Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const Trade53Message*>(buffer);
    }
};

#pragma pack(pop)
}
