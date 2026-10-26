#pragma once

#include "../types/MdFeedType.hpp"
#include "../types/MarketDepth.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct FeedTypesGroup {

    MdFeedType md_feed_type;
    MarketDepth market_depth;

    // parse method
    static FeedTypesGroup* parse(std::byte* buffer) {
        return reinterpret_cast<FeedTypesGroup*>(buffer);
    }

    // parse method const
    static const FeedTypesGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const FeedTypesGroup*>(buffer);
    }
};

#pragma pack(pop)
}
