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

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

#pragma pack(push, 1)

// Published every 60 seconds on a separate multicast channel. Provides high, low, open, close and total volume per series.
struct OptionsOutrightSeriesSummaryMessage {

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
    static OptionsOutrightSeriesSummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OptionsOutrightSeriesSummaryMessage*>(buffer);
    }

    // parse method const
    static const OptionsOutrightSeriesSummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionsOutrightSeriesSummaryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OptionsOutrightSeriesSummaryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OptionsOutrightSeriesSummaryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
