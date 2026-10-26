#pragma once

#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/TradeDate.hpp"
#include "../types/MdFuturePrice.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

#pragma pack(push, 1)

// HighPrice_24Message
struct HighPrice24Message {

    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    MdUpdateAction md_update_action;
    TradeDate trade_date;
    MdFuturePrice md_future_price;
    MdEntryTimestamp md_entry_timestamp;
    RptSeq rpt_seq;

    // parse method
    static HighPrice24Message* parse(std::byte* buffer) {
        return reinterpret_cast<HighPrice24Message*>(buffer);
    }

    // parse method const
    static const HighPrice24Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const HighPrice24Message*>(buffer);
    }
};

#pragma pack(pop)
}
