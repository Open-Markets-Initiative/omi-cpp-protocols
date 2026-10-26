#pragma once

#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/OrderId.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/PrintableFlag.hpp"
#include "../types/Reserved1.hpp"
#include "../types/TradeCond1.hpp"
#include "../types/Reserved3.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

#pragma pack(push, 1)

// Sent when an order is partially or fully executed.
struct OptionsOrderExecutionMessage {

    SourceTimeNs source_time_ns;
    SeriesIndex series_index;
    SeriesSeqNum series_seq_num;
    OrderId order_id;
    TradeId trade_id;
    Price price;
    Volume volume;
    PrintableFlag printable_flag;
    Reserved1 reserved_1;
    TradeCond1 trade_cond_1;
    Reserved3 reserved_3;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 303;

    // parse method
    static OptionsOrderExecutionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OptionsOrderExecutionMessage*>(buffer);
    }

    // parse method const
    static const OptionsOrderExecutionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionsOrderExecutionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OptionsOrderExecutionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OptionsOrderExecutionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
