#pragma once

#include "../types/TransactTime.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/Padding2.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

// MDIncrementalRefreshLimitsBanding
struct MdIncrementalRefreshLimitsBandingLegacy {

    TransactTime transact_time;
    MatchEventIndicator match_event_indicator;
    Padding2 padding_2;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 34;

    // parse method
    static MdIncrementalRefreshLimitsBandingLegacy* parse(std::byte* buffer) {
        return reinterpret_cast<MdIncrementalRefreshLimitsBandingLegacy*>(buffer);
    }

    // parse method const
    static const MdIncrementalRefreshLimitsBandingLegacy* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdIncrementalRefreshLimitsBandingLegacy*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MdIncrementalRefreshLimitsBandingLegacy* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const MdIncrementalRefreshLimitsBandingLegacy*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
