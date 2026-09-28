#pragma once

#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/OpenCloseSettlFlag.hpp"
#include "../types/Offset11Padding1.hpp"
#include "../types/MdFuturePrice.hpp"
#include "../types/NetChgPrevDay.hpp"
#include "../types/TradeDate.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"
#include "../types/Padding2.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

#pragma pack(push, 1)

// OpeningPrice_15Message
struct OpeningPrice15Message {

    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    MdUpdateAction md_update_action;
    OpenCloseSettlFlag open_close_settl_flag;
    Offset11Padding1 offset_11_padding_1;
    MdFuturePrice md_future_price;
    NetChgPrevDay net_chg_prev_day;
    TradeDate trade_date;
    MdEntryTimestamp md_entry_timestamp;
    RptSeq rpt_seq;
    Padding2 padding_2;

    // parse method
    static OpeningPrice15Message* parse(std::byte* buffer) {
        return reinterpret_cast<OpeningPrice15Message*>(buffer);
    }

    // parse method const
    static const OpeningPrice15Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const OpeningPrice15Message*>(buffer);
    }
};

#pragma pack(pop)
}
