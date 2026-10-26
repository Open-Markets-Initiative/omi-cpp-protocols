#pragma once

#include "../types/SeriesIndex.hpp"
#include "../types/MarketId.hpp"
#include "../types/SystemId.hpp"
#include "../types/NoOfLegs.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

#pragma pack(push, 1)

// Published over the real-time data channels at system startup or in the context of a refresh sequence. Provides referential data for a single specified options complex series.
struct ComplexSeriesIndexMappingMessage {

    SeriesIndex series_index;
    MarketId market_id;
    SystemId system_id;
    NoOfLegs no_of_legs;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 60;

    // parse method
    static ComplexSeriesIndexMappingMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ComplexSeriesIndexMappingMessage*>(buffer);
    }

    // parse method const
    static const ComplexSeriesIndexMappingMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ComplexSeriesIndexMappingMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ComplexSeriesIndexMappingMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ComplexSeriesIndexMappingMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
