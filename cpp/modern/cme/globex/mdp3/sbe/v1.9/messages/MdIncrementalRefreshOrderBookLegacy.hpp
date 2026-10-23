#pragma once

#include "../types/TransactTime.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/Padding2.hpp"
#include "../structs/MessageHeader.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

// MDIncrementalRefreshOrderBook
struct MdIncrementalRefreshOrderBookLegacy {

    TransactTime transact_time;
    MatchEventIndicator match_event_indicator;
    Padding2 padding_2;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 43;

    // parse method
    static MdIncrementalRefreshOrderBookLegacy* parse(std::byte* buffer) {
        return reinterpret_cast<MdIncrementalRefreshOrderBookLegacy*>(buffer);
    }

    // parse method const
    static const MdIncrementalRefreshOrderBookLegacy* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdIncrementalRefreshOrderBookLegacy*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MdIncrementalRefreshOrderBookLegacy* parse(const MessageHeader* header) {
        return reinterpret_cast<const MdIncrementalRefreshOrderBookLegacy*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
