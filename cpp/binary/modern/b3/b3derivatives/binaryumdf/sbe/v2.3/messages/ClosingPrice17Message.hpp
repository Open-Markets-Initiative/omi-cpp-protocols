#pragma once

#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/OpenCloseSettlFlag.hpp"
#include "../types/Offset10Padding2.hpp"
#include "../types/MdCorporatePrice.hpp"
#include "../types/LastTradeDate.hpp"
#include "../types/TradeDate.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

#pragma pack(push, 1)

// ClosingPrice_17Message
struct ClosingPrice17Message {

    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    OpenCloseSettlFlag open_close_settl_flag;
    Offset10Padding2 offset_10_padding_2;
    MdCorporatePrice md_corporate_price;
    LastTradeDate last_trade_date;
    TradeDate trade_date;
    MdEntryTimestamp md_entry_timestamp;
    RptSeq rpt_seq;

    // parse method
    static ClosingPrice17Message* parse(std::byte* buffer) {
        return reinterpret_cast<ClosingPrice17Message*>(buffer);
    }

    // parse method const
    static const ClosingPrice17Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const ClosingPrice17Message*>(buffer);
    }
};

#pragma pack(pop)
}
