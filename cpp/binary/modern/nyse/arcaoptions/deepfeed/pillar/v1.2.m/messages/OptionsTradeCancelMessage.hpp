#pragma once

#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/TradeId.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

#pragma pack(push, 1)

// Published when an earlier trade has been reported in error.
struct OptionsTradeCancelMessage {

    SourceTimeNs source_time_ns;
    SeriesIndex series_index;
    SeriesSeqNum series_seq_num;
    TradeId trade_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 312;

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
