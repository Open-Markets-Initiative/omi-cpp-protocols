#pragma once

#include <cstddef>
#include "../structs/RecordHeader.hpp"
#include "../types/OrderId.hpp"
#include "../types/Price.hpp"
#include "../types/SizeType.hpp"
#include "../types/Flags.hpp"
#include "../types/ChannelId.hpp"
#include "../types/Action.hpp"
#include "../types/Side.hpp"
#include "../types/TsRecv.hpp"
#include "../types/TsInDelta.hpp"
#include "../types/Sequence.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v3;

#pragma pack(push, 1)

// Mbo Msg
struct mbo_msg {

    struct fields_type {
        dbn_normalized::order_id order_id;
        dbn_normalized::price price;
        dbn_normalized::size_type size;
        dbn_normalized::flags flags;
        dbn_normalized::channel_id channel_id;
        dbn_normalized::action action;
        dbn_normalized::side side;
        dbn_normalized::ts_recv ts_recv;
        dbn_normalized::ts_in_delta ts_in_delta;
        dbn_normalized::sequence sequence;
    };

    dbn_normalized::record_header header = {record_length((sizeof(dbn_normalized::record_header) + sizeof(fields_type)) / 4), rtype::enum_type::market_by_order, {}, {}, {}};

    fields_type fields;

    // parse method
    static mbo_msg* parse(std::byte* buffer) {
        return reinterpret_cast<mbo_msg*>(buffer);
    }

    // parse method const
    static const mbo_msg* parse(const std::byte* buffer) {
        return reinterpret_cast<const mbo_msg*>(buffer);
    }

};

// layout verification
static_assert(offsetof(mbo_msg::fields_type, order_id) == 0, "unexpected offset of mbo_msg::fields_type::order_id");
static_assert(offsetof(mbo_msg::fields_type, price) == 8, "unexpected offset of mbo_msg::fields_type::price");
static_assert(offsetof(mbo_msg::fields_type, size) == 16, "unexpected offset of mbo_msg::fields_type::size");
static_assert(offsetof(mbo_msg::fields_type, flags) == 20, "unexpected offset of mbo_msg::fields_type::flags");
static_assert(offsetof(mbo_msg::fields_type, channel_id) == 21, "unexpected offset of mbo_msg::fields_type::channel_id");
static_assert(offsetof(mbo_msg::fields_type, action) == 22, "unexpected offset of mbo_msg::fields_type::action");
static_assert(offsetof(mbo_msg::fields_type, side) == 23, "unexpected offset of mbo_msg::fields_type::side");
static_assert(offsetof(mbo_msg::fields_type, ts_recv) == 24, "unexpected offset of mbo_msg::fields_type::ts_recv");
static_assert(offsetof(mbo_msg::fields_type, ts_in_delta) == 32, "unexpected offset of mbo_msg::fields_type::ts_in_delta");
static_assert(offsetof(mbo_msg::fields_type, sequence) == 36, "unexpected offset of mbo_msg::fields_type::sequence");
static_assert(sizeof(mbo_msg::fields_type) == 40, "unexpected sizeof mbo_msg::fields_type");
static_assert(sizeof(mbo_msg) == sizeof(dbn_normalized::record_header) + 40, "unexpected sizeof mbo_msg");

#pragma pack(pop)
}
