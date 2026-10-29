#pragma once

#include "../types/MarketDayIdentifier.hpp"
#include "../types/FeedIdentifier.hpp"
#include "../types/Sequence.hpp"
#include "../types/Count.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

#pragma pack(push, 1)

struct PacketHeader {

    MarketDayIdentifier market_day_identifier;
    FeedIdentifier feed_identifier;
    Sequence sequence;
    Count count;

    // parse method
    static PacketHeader* parse(std::byte* buffer) {
        return reinterpret_cast<PacketHeader*>(buffer);
    }

    // parse method const
    static const PacketHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const PacketHeader*>(buffer);
    }
};

#pragma pack(pop)
}
