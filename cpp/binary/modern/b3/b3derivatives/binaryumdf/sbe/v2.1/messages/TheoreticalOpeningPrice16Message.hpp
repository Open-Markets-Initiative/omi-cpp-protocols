#pragma once

#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/TradeDate.hpp"
#include "../types/MdCorporateOffsetPriceOptional.hpp"
#include "../types/MdEntrySizeQuantityOptional.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

#pragma pack(push, 1)

// TheoreticalOpeningPrice_16Message
struct TheoreticalOpeningPrice16Message {

    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    MdUpdateAction md_update_action;
    TradeDate trade_date;
    MdCorporateOffsetPriceOptional md_corporate_offset_price_optional;
    MdEntrySizeQuantityOptional md_entry_size_quantity_optional;
    MdEntryTimestamp md_entry_timestamp;
    RptSeq rpt_seq;

    // parse method
    static TheoreticalOpeningPrice16Message* parse(std::byte* buffer) {
        return reinterpret_cast<TheoreticalOpeningPrice16Message*>(buffer);
    }

    // parse method const
    static const TheoreticalOpeningPrice16Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const TheoreticalOpeningPrice16Message*>(buffer);
    }
};

#pragma pack(pop)
}
