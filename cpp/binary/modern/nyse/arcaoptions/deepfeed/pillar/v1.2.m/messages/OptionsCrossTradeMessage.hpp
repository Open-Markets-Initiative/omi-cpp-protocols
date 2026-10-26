#pragma once

#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/CrossId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/CrossType.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

#pragma pack(push, 1)

// Published on completion of a crossing from the opening and re-opening auction, showing the bulk volume that traded in the auction.
struct OptionsCrossTradeMessage {

    SourceTimeNs source_time_ns;
    SeriesIndex series_index;
    SeriesSeqNum series_seq_num;
    CrossId cross_id;
    Price price;
    Volume volume;
    CrossType cross_type;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 311;

    // parse method
    static OptionsCrossTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OptionsCrossTradeMessage*>(buffer);
    }

    // parse method const
    static const OptionsCrossTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionsCrossTradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OptionsCrossTradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OptionsCrossTradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
