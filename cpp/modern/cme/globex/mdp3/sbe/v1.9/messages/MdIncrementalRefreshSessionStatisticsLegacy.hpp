#pragma once

#include "../types/TransactTime.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/Padding2.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

// MDIncrementalRefreshSessionStatistics
struct MdIncrementalRefreshSessionStatisticsLegacy {

    TransactTime transact_time;
    MatchEventIndicator match_event_indicator;
    Padding2 padding_2;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 35;

    // parse method
    static MdIncrementalRefreshSessionStatisticsLegacy* parse(std::byte* buffer) {
        return reinterpret_cast<MdIncrementalRefreshSessionStatisticsLegacy*>(buffer);
    }

    // parse method const
    static const MdIncrementalRefreshSessionStatisticsLegacy* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdIncrementalRefreshSessionStatisticsLegacy*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MdIncrementalRefreshSessionStatisticsLegacy* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const MdIncrementalRefreshSessionStatisticsLegacy*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
