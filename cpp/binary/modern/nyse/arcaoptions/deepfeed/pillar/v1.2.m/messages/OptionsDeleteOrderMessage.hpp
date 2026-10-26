#pragma once

#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/OrderId.hpp"
#include "../types/Reserved1.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

#pragma pack(push, 1)

// Published when an order is taken off of the book for any reason except for full execution.
struct OptionsDeleteOrderMessage {

    SourceTimeNs source_time_ns;
    SeriesIndex series_index;
    SeriesSeqNum series_seq_num;
    OrderId order_id;
    Reserved1 reserved_1;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 302;

    // parse method
    static OptionsDeleteOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OptionsDeleteOrderMessage*>(buffer);
    }

    // parse method const
    static const OptionsDeleteOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionsDeleteOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OptionsDeleteOrderMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OptionsDeleteOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
