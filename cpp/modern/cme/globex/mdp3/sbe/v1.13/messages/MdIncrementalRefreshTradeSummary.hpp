#pragma once

#include "../types/TransactTime.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/Padding2.hpp"
#include "../structs/MessageHeader.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

// MDIncrementalRefreshTradeSummary
struct MdIncrementalRefreshTradeSummary {

    TransactTime transact_time;
    MatchEventIndicator match_event_indicator;
    Padding2 padding_2;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 48;

    // parse method
    static MdIncrementalRefreshTradeSummary* parse(std::byte* buffer) {
        return reinterpret_cast<MdIncrementalRefreshTradeSummary*>(buffer);
    }

    // parse method const
    static const MdIncrementalRefreshTradeSummary* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdIncrementalRefreshTradeSummary*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MdIncrementalRefreshTradeSummary* parse(const MessageHeader* header) {
        return reinterpret_cast<const MdIncrementalRefreshTradeSummary*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
