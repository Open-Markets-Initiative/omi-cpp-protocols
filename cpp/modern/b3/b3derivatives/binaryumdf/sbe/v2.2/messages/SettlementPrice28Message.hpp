#pragma once

#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/Offset9Padding1.hpp"
#include "../types/TradeDate.hpp"
#include "../types/MdFuturePrice.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/OpenCloseSettlFlag.hpp"
#include "../types/PriceType.hpp"
#include "../types/SettlPriceType.hpp"
#include "../types/RptSeq.hpp"
#include "../types/Padding1.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

#pragma pack(push, 1)

// SettlementPrice_28Message
struct SettlementPrice28Message {

    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    Offset9Padding1 offset_9_padding_1;
    TradeDate trade_date;
    MdFuturePrice md_future_price;
    MdEntryTimestamp md_entry_timestamp;
    OpenCloseSettlFlag open_close_settl_flag;
    PriceType price_type;
    SettlPriceType settl_price_type;
    RptSeq rpt_seq;
    Padding1 padding_1;

    // parse method
    static SettlementPrice28Message* parse(std::byte* buffer) {
        return reinterpret_cast<SettlementPrice28Message*>(buffer);
    }

    // parse method const
    static const SettlementPrice28Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const SettlementPrice28Message*>(buffer);
    }
};

#pragma pack(pop)
}
