#pragma once

#include <cstddef>
#include "../types/BidPx.hpp"
#include "../types/AskPx.hpp"
#include "../types/BidSz.hpp"
#include "../types/AskSz.hpp"
#include "../types/BidPb.hpp"
#include "../types/Reserved2.hpp"
#include "../types/AskPb.hpp"
#include "../types/SecondReserved2.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v3;

#pragma pack(push, 1)

struct consolidated_bid_ask_pair {

    dbn_normalized::bid_px bid_px;
    dbn_normalized::ask_px ask_px;
    dbn_normalized::bid_sz bid_sz;
    dbn_normalized::ask_sz ask_sz;
    dbn_normalized::bid_pb bid_pb;
    dbn_normalized::reserved_2 reserved_2;
    dbn_normalized::ask_pb ask_pb;
    dbn_normalized::second_reserved_2 second_reserved_2;

    // parse method
    static consolidated_bid_ask_pair* parse(std::byte* buffer) {
        return reinterpret_cast<consolidated_bid_ask_pair*>(buffer);
    }

    // parse method const
    static const consolidated_bid_ask_pair* parse(const std::byte* buffer) {
        return reinterpret_cast<const consolidated_bid_ask_pair*>(buffer);
    }
};

// layout verification
static_assert(offsetof(consolidated_bid_ask_pair, bid_px) == 0, "unexpected offset of consolidated_bid_ask_pair::bid_px");
static_assert(offsetof(consolidated_bid_ask_pair, ask_px) == 8, "unexpected offset of consolidated_bid_ask_pair::ask_px");
static_assert(offsetof(consolidated_bid_ask_pair, bid_sz) == 16, "unexpected offset of consolidated_bid_ask_pair::bid_sz");
static_assert(offsetof(consolidated_bid_ask_pair, ask_sz) == 20, "unexpected offset of consolidated_bid_ask_pair::ask_sz");
static_assert(offsetof(consolidated_bid_ask_pair, bid_pb) == 24, "unexpected offset of consolidated_bid_ask_pair::bid_pb");
static_assert(offsetof(consolidated_bid_ask_pair, reserved_2) == 26, "unexpected offset of consolidated_bid_ask_pair::reserved_2");
static_assert(offsetof(consolidated_bid_ask_pair, ask_pb) == 28, "unexpected offset of consolidated_bid_ask_pair::ask_pb");
static_assert(offsetof(consolidated_bid_ask_pair, second_reserved_2) == 30, "unexpected offset of consolidated_bid_ask_pair::second_reserved_2");
static_assert(sizeof(consolidated_bid_ask_pair) == 32, "unexpected sizeof consolidated_bid_ask_pair");

#pragma pack(pop)
}
