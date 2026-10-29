#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/HighPrice.hpp"
#include "../types/LowPrice.hpp"
#include "../types/Open.hpp"
#include "../types/Close.hpp"
#include "../types/TotalVolume.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

#pragma pack(push, 1)

// The Series Summary message will provide the following trade statistics per series: high, low, open, close and total volume
struct OutrightSeriesSummaryMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SeriesIndex series_index;
    HighPrice high_price;
    LowPrice low_price;
    Open open;
    Close close;
    TotalVolume total_volume;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 323;

    // parse method
    static OutrightSeriesSummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OutrightSeriesSummaryMessage*>(buffer);
    }

    // parse method const
    static const OutrightSeriesSummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OutrightSeriesSummaryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OutrightSeriesSummaryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OutrightSeriesSummaryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
