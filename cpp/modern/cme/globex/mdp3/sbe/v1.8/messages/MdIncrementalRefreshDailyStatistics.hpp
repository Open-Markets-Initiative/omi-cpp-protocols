#pragma once

#include "../types/TransactTime.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/Padding2.hpp"
#include "../structs/MessageHeader.hpp"

namespace cme::mdp3::v8 {

#pragma pack(push, 1)

// MDIncrementalRefreshDailyStatistics
struct MdIncrementalRefreshDailyStatistics {

    TransactTime transact_time;
    MatchEventIndicator match_event_indicator;
    Padding2 padding_2;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 33;

    // parse method
    static MdIncrementalRefreshDailyStatistics* parse(std::byte* buffer) {
        return reinterpret_cast<MdIncrementalRefreshDailyStatistics*>(buffer);
    }

    // parse method const
    static const MdIncrementalRefreshDailyStatistics* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdIncrementalRefreshDailyStatistics*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MdIncrementalRefreshDailyStatistics* parse(const MessageHeader* header) {
        return reinterpret_cast<const MdIncrementalRefreshDailyStatistics*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
