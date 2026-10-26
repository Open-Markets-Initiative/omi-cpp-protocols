#pragma once

#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeVolume.hpp"
#include "../types/VwapPx.hpp"
#include "../types/NetChgPrevDay.hpp"
#include "../types/NumberOfTrades.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

#pragma pack(push, 1)

// ExecutionStatistics_56Message
struct ExecutionStatistics56Message {

    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    TradingSessionId trading_session_id;
    TradeDate trade_date;
    TradeVolume trade_volume;
    VwapPx vwap_px;
    NetChgPrevDay net_chg_prev_day;
    NumberOfTrades number_of_trades;
    MdEntryTimestamp md_entry_timestamp;
    RptSeq rpt_seq;

    // parse method
    static ExecutionStatistics56Message* parse(std::byte* buffer) {
        return reinterpret_cast<ExecutionStatistics56Message*>(buffer);
    }

    // parse method const
    static const ExecutionStatistics56Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const ExecutionStatistics56Message*>(buffer);
    }
};

#pragma pack(pop)
}
