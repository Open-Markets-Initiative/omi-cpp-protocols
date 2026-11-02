#pragma once

#include "../types/BidPx.hpp"
#include "../types/AskPx.hpp"
#include "../types/BidSz.hpp"
#include "../types/AskSz.hpp"
#include "../types/BidPb.hpp"
#include "../types/Reserved2.hpp"
#include "../types/AskPb.hpp"
#include "../types/SecondReserved2.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

#pragma pack(push, 1)

struct ConsolidatedBidAskPair {

    BidPx bid_px;
    AskPx ask_px;
    BidSz bid_sz;
    AskSz ask_sz;
    BidPb bid_pb;
    Reserved2 reserved_2;
    AskPb ask_pb;
    SecondReserved2 second_reserved_2;

    // parse method
    static ConsolidatedBidAskPair* parse(std::byte* buffer) {
        return reinterpret_cast<ConsolidatedBidAskPair*>(buffer);
    }

    // parse method const
    static const ConsolidatedBidAskPair* parse(const std::byte* buffer) {
        return reinterpret_cast<const ConsolidatedBidAskPair*>(buffer);
    }
};

#pragma pack(pop)
}
