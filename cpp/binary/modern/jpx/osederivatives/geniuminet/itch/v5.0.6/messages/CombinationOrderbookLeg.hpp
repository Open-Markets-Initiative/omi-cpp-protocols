#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/CombinationOrderbookId.hpp"
#include "../types/LegOrderbookId.hpp"
#include "../types/LegSide.hpp"
#include "../types/LegRatio.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

#pragma pack(push, 1)

// Mapping between a combination orderbook and its leg orderbooks.
struct CombinationOrderbookLeg {

    Nanoseconds nanoseconds;
    CombinationOrderbookId combination_orderbook_id;
    LegOrderbookId leg_orderbook_id;
    LegSide leg_side;
    LegRatio leg_ratio;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'M';

    // parse method
    static CombinationOrderbookLeg* parse(std::byte* buffer) {
        return reinterpret_cast<CombinationOrderbookLeg*>(buffer);
    }

    // parse method const
    static const CombinationOrderbookLeg* parse(const std::byte* buffer) {
        return reinterpret_cast<const CombinationOrderbookLeg*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const CombinationOrderbookLeg* parse(const MessageHeader* header) {
        return reinterpret_cast<const CombinationOrderbookLeg*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
