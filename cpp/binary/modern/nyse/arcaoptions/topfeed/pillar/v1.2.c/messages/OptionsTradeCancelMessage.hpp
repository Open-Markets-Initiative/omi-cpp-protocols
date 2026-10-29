#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/OriginalTradeId.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

#pragma pack(push, 1)

// In the event that an earlier trade has been reported in error, an Options Trade Cancel message is sent
struct OptionsTradeCancelMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SeriesIndex series_index;
    SeriesSeqNum series_seq_num;
    OriginalTradeId original_trade_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 321;

    // parse method
    static OptionsTradeCancelMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OptionsTradeCancelMessage*>(buffer);
    }

    // parse method const
    static const OptionsTradeCancelMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionsTradeCancelMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OptionsTradeCancelMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OptionsTradeCancelMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
