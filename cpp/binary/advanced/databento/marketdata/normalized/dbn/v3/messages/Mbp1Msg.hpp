// Databento.MarketData.Normalized.Dbn.v3: messages/Mbp1Msg.hpp
#pragma once

#include <cstddef>
#include "../structs/RecordHeader.hpp"
#include "../types/Price.hpp"
#include "../types/SizeType.hpp"
#include "../types/Action.hpp"
#include "../types/Side.hpp"
#include "../types/Flags.hpp"
#include "../types/Depth.hpp"
#include "../types/TsRecv.hpp"
#include "../types/TsInDelta.hpp"
#include "../types/Sequence.hpp"
#include "../structs/BidAskPair.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v3;

#pragma pack(push, 1)

// Mbp 1 Msg
struct mbp_1_msg {

    struct fields_type {
        dbn_normalized::price price;
        dbn_normalized::size_type size;
        dbn_normalized::action action;
        dbn_normalized::side side;
        dbn_normalized::flags flags;
        dbn_normalized::depth depth;
        dbn_normalized::ts_recv ts_recv;
        dbn_normalized::ts_in_delta ts_in_delta;
        dbn_normalized::sequence sequence;
        dbn_normalized::bid_ask_pair bid_ask_pair;
    };

    dbn_normalized::record_header header = {record_length((sizeof(dbn_normalized::record_header) + sizeof(fields_type)) / 4), rtype::enum_type::market_by_price_1, {}, {}, {}};

    fields_type fields;

    // parse method
    static mbp_1_msg* parse(std::byte* buffer) {
        return reinterpret_cast<mbp_1_msg*>(buffer);
    }

    // parse method const
    static const mbp_1_msg* parse(const std::byte* buffer) {
        return reinterpret_cast<const mbp_1_msg*>(buffer);
    }

};

// layout verification
static_assert(offsetof(mbp_1_msg::fields_type, price) == 0, "unexpected offset of mbp_1_msg::fields_type::price");
static_assert(offsetof(mbp_1_msg::fields_type, size) == 8, "unexpected offset of mbp_1_msg::fields_type::size");
static_assert(offsetof(mbp_1_msg::fields_type, action) == 12, "unexpected offset of mbp_1_msg::fields_type::action");
static_assert(offsetof(mbp_1_msg::fields_type, side) == 13, "unexpected offset of mbp_1_msg::fields_type::side");
static_assert(offsetof(mbp_1_msg::fields_type, flags) == 14, "unexpected offset of mbp_1_msg::fields_type::flags");
static_assert(offsetof(mbp_1_msg::fields_type, depth) == 15, "unexpected offset of mbp_1_msg::fields_type::depth");
static_assert(offsetof(mbp_1_msg::fields_type, ts_recv) == 16, "unexpected offset of mbp_1_msg::fields_type::ts_recv");
static_assert(offsetof(mbp_1_msg::fields_type, ts_in_delta) == 24, "unexpected offset of mbp_1_msg::fields_type::ts_in_delta");
static_assert(offsetof(mbp_1_msg::fields_type, sequence) == 28, "unexpected offset of mbp_1_msg::fields_type::sequence");
static_assert(offsetof(mbp_1_msg::fields_type, bid_ask_pair) == 32, "unexpected offset of mbp_1_msg::fields_type::bid_ask_pair");
static_assert(sizeof(mbp_1_msg::fields_type) == 64, "unexpected sizeof mbp_1_msg::fields_type");
static_assert(sizeof(mbp_1_msg) == sizeof(dbn_normalized::record_header) + 64, "unexpected sizeof mbp_1_msg");

#pragma pack(pop)
}
