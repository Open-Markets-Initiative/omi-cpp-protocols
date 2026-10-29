#pragma once

#include "../types/TransactTime.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/Padding2.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v5 {

#pragma pack(push, 1)

// MDIncrementalRefreshBook
struct MdIncrementalRefreshBook {

    TransactTime transact_time;
    MatchEventIndicator match_event_indicator;
    Padding2 padding_2;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 32;

    // parse method
    static MdIncrementalRefreshBook* parse(std::byte* buffer) {
        return reinterpret_cast<MdIncrementalRefreshBook*>(buffer);
    }

    // parse method const
    static const MdIncrementalRefreshBook* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdIncrementalRefreshBook*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MdIncrementalRefreshBook* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const MdIncrementalRefreshBook*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
