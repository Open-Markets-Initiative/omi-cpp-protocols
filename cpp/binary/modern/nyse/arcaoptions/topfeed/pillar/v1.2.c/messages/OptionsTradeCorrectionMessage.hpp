#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/OriginalTradeId.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../structs/CorrectionCondition.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

#pragma pack(push, 1)

// In the event that an earlier trade has been reported with one or multiple fields in error
struct OptionsTradeCorrectionMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SeriesIndex series_index;
    SeriesSeqNum series_seq_num;
    OriginalTradeId original_trade_id;
    TradeId trade_id;
    Price price;
    Volume volume;
    CorrectionCondition correction_condition;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 322;

    // parse method
    static OptionsTradeCorrectionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OptionsTradeCorrectionMessage*>(buffer);
    }

    // parse method const
    static const OptionsTradeCorrectionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionsTradeCorrectionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OptionsTradeCorrectionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OptionsTradeCorrectionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
