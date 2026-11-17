// Databento.MarketData.Normalized.Dbn.v3: structs/BidAskPair.hpp
#pragma once

#include <cstddef>
#include "../types/BidPx.hpp"
#include "../types/AskPx.hpp"
#include "../types/BidSz.hpp"
#include "../types/AskSz.hpp"
#include "../types/BidCt.hpp"
#include "../types/AskCt.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v3;

#pragma pack(push, 1)

struct bid_ask_pair {

    dbn_normalized::bid_px bid_px;
    dbn_normalized::ask_px ask_px;
    dbn_normalized::bid_sz bid_sz;
    dbn_normalized::ask_sz ask_sz;
    dbn_normalized::bid_ct bid_ct;
    dbn_normalized::ask_ct ask_ct;

    // parse method
    static bid_ask_pair* parse(std::byte* buffer) {
        return reinterpret_cast<bid_ask_pair*>(buffer);
    }

    // parse method const
    static const bid_ask_pair* parse(const std::byte* buffer) {
        return reinterpret_cast<const bid_ask_pair*>(buffer);
    }
};

// layout verification
static_assert(offsetof(bid_ask_pair, bid_px) == 0, "unexpected offset of bid_ask_pair::bid_px");
static_assert(offsetof(bid_ask_pair, ask_px) == 8, "unexpected offset of bid_ask_pair::ask_px");
static_assert(offsetof(bid_ask_pair, bid_sz) == 16, "unexpected offset of bid_ask_pair::bid_sz");
static_assert(offsetof(bid_ask_pair, ask_sz) == 20, "unexpected offset of bid_ask_pair::ask_sz");
static_assert(offsetof(bid_ask_pair, bid_ct) == 24, "unexpected offset of bid_ask_pair::bid_ct");
static_assert(offsetof(bid_ask_pair, ask_ct) == 28, "unexpected offset of bid_ask_pair::ask_ct");
static_assert(sizeof(bid_ask_pair) == 32, "unexpected sizeof bid_ask_pair");

#pragma pack(pop)
}
