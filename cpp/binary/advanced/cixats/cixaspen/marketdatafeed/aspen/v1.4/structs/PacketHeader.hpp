#pragma once

#include <cstddef>
#include "../types/MarketDayIdentifier.hpp"
#include "../types/FeedIdentifier.hpp"
#include "../types/Sequence.hpp"
#include "../types/Count.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

namespace aspen_marketdatafeed = ::cixats::cixaspen::marketdatafeed::aspen::v1_4;

#pragma pack(push, 1)

struct packet_header {

    aspen_marketdatafeed::market_day_identifier market_day_identifier;
    aspen_marketdatafeed::feed_identifier feed_identifier;
    aspen_marketdatafeed::sequence sequence;
    aspen_marketdatafeed::count count;

    // parse method
    static packet_header* parse(std::byte* buffer) {
        return reinterpret_cast<packet_header*>(buffer);
    }

    // parse method const
    static const packet_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const packet_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(packet_header, market_day_identifier) == 0, "unexpected offset of packet_header::market_day_identifier");
static_assert(offsetof(packet_header, feed_identifier) == 9, "unexpected offset of packet_header::feed_identifier");
static_assert(offsetof(packet_header, sequence) == 10, "unexpected offset of packet_header::sequence");
static_assert(offsetof(packet_header, count) == 18, "unexpected offset of packet_header::count");
static_assert(sizeof(packet_header) == 20, "unexpected sizeof packet_header");

#pragma pack(pop)
}
