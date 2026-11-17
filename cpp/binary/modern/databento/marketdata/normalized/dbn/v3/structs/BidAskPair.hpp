// Databento.MarketData.Normalized.Dbn.v3: structs/BidAskPair.hpp
#pragma once

#include "../types/BidPx.hpp"
#include "../types/AskPx.hpp"
#include "../types/BidSz.hpp"
#include "../types/AskSz.hpp"
#include "../types/BidCt.hpp"
#include "../types/AskCt.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

#pragma pack(push, 1)

struct BidAskPair {

    BidPx bid_px;
    AskPx ask_px;
    BidSz bid_sz;
    AskSz ask_sz;
    BidCt bid_ct;
    AskCt ask_ct;

    // parse method
    static BidAskPair* parse(std::byte* buffer) {
        return reinterpret_cast<BidAskPair*>(buffer);
    }

    // parse method const
    static const BidAskPair* parse(const std::byte* buffer) {
        return reinterpret_cast<const BidAskPair*>(buffer);
    }
};

#pragma pack(pop)
}
