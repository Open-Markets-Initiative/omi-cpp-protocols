// Databento.MarketData.Normalized.Dbn.v2: messages/TradeMsg.hpp
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

namespace databento::marketdata::normalized::dbn::v2 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v2;

#pragma pack(push, 1)

// Trade Msg
struct trade_msg {

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
    };

    dbn_normalized::record_header header = {record_length((sizeof(dbn_normalized::record_header) + sizeof(fields_type)) / 4), rtype::enum_type::market_by_price_0, {}, {}, {}};

    fields_type fields;

    // parse method
    static trade_msg* parse(std::byte* buffer) {
        return reinterpret_cast<trade_msg*>(buffer);
    }

    // parse method const
    static const trade_msg* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_msg*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_msg::fields_type, price) == 0, "unexpected offset of trade_msg::fields_type::price");
static_assert(offsetof(trade_msg::fields_type, size) == 8, "unexpected offset of trade_msg::fields_type::size");
static_assert(offsetof(trade_msg::fields_type, action) == 12, "unexpected offset of trade_msg::fields_type::action");
static_assert(offsetof(trade_msg::fields_type, side) == 13, "unexpected offset of trade_msg::fields_type::side");
static_assert(offsetof(trade_msg::fields_type, flags) == 14, "unexpected offset of trade_msg::fields_type::flags");
static_assert(offsetof(trade_msg::fields_type, depth) == 15, "unexpected offset of trade_msg::fields_type::depth");
static_assert(offsetof(trade_msg::fields_type, ts_recv) == 16, "unexpected offset of trade_msg::fields_type::ts_recv");
static_assert(offsetof(trade_msg::fields_type, ts_in_delta) == 24, "unexpected offset of trade_msg::fields_type::ts_in_delta");
static_assert(offsetof(trade_msg::fields_type, sequence) == 28, "unexpected offset of trade_msg::fields_type::sequence");
static_assert(sizeof(trade_msg::fields_type) == 32, "unexpected sizeof trade_msg::fields_type");
static_assert(sizeof(trade_msg) == sizeof(dbn_normalized::record_header) + 32, "unexpected sizeof trade_msg");

#pragma pack(pop)
}
