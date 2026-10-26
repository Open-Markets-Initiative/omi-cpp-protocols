#pragma once

#include "../types/TransactTime.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/Padding2.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

// MDIncrementalRefreshVolume
struct MdIncrementalRefreshVolume {

    TransactTime transact_time;
    MatchEventIndicator match_event_indicator;
    Padding2 padding_2;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 37;

    // parse method
    static MdIncrementalRefreshVolume* parse(std::byte* buffer) {
        return reinterpret_cast<MdIncrementalRefreshVolume*>(buffer);
    }

    // parse method const
    static const MdIncrementalRefreshVolume* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdIncrementalRefreshVolume*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MdIncrementalRefreshVolume* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const MdIncrementalRefreshVolume*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
