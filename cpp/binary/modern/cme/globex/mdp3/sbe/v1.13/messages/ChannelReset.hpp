#pragma once

#include "../types/TransactTime.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

// ChannelReset
struct ChannelReset {

    TransactTime transact_time;
    MatchEventIndicator match_event_indicator;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 4;

    // parse method
    static ChannelReset* parse(std::byte* buffer) {
        return reinterpret_cast<ChannelReset*>(buffer);
    }

    // parse method const
    static const ChannelReset* parse(const std::byte* buffer) {
        return reinterpret_cast<const ChannelReset*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ChannelReset* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const ChannelReset*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
