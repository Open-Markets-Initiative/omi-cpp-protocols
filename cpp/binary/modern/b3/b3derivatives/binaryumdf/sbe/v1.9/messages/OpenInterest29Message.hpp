#pragma once

#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/Offset9Padding1.hpp"
#include "../types/TradeDate.hpp"
#include "../types/MdEntrySizeQuantity.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

#pragma pack(push, 1)

// OpenInterest_29Message
struct OpenInterest29Message {

    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    Offset9Padding1 offset_9_padding_1;
    TradeDate trade_date;
    MdEntrySizeQuantity md_entry_size_quantity;
    MdEntryTimestamp md_entry_timestamp;
    RptSeq rpt_seq;

    // parse method
    static OpenInterest29Message* parse(std::byte* buffer) {
        return reinterpret_cast<OpenInterest29Message*>(buffer);
    }

    // parse method const
    static const OpenInterest29Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const OpenInterest29Message*>(buffer);
    }
};

#pragma pack(pop)
}
