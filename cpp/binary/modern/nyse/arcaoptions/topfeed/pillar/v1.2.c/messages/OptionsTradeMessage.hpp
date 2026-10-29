#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../structs/TradeCondition.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

#pragma pack(push, 1)

// An Options Trade message is sent when there is an execution on the order book.
struct OptionsTradeMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SeriesIndex series_index;
    SeriesSeqNum series_seq_num;
    TradeId trade_id;
    Price price;
    Volume volume;
    TradeCondition trade_condition;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 320;

    // parse method
    static OptionsTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OptionsTradeMessage*>(buffer);
    }

    // parse method const
    static const OptionsTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionsTradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OptionsTradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OptionsTradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
