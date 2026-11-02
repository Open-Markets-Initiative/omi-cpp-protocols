#pragma once

#include <cstddef>
#include "../structs/RecordHeader.hpp"
#include "../types/Price.hpp"
#include "../types/SizeType.hpp"
#include "../types/Reserved1.hpp"
#include "../types/Side.hpp"
#include "../types/Flags.hpp"
#include "../types/SecondReserved1.hpp"
#include "../types/TsRecv.hpp"
#include "../types/Reserved4.hpp"
#include "../types/Sequence.hpp"
#include "../structs/BidAskPair.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v2;

#pragma pack(push, 1)

// Bbo Msg
struct bbo_msg {

    struct fields_type {
        dbn_normalized::price price;
        dbn_normalized::size_type size;
        dbn_normalized::reserved_1 reserved_1;
        dbn_normalized::side side;
        dbn_normalized::flags flags;
        dbn_normalized::second_reserved_1 second_reserved_1;
        dbn_normalized::ts_recv ts_recv;
        dbn_normalized::reserved_4 reserved_4;
        dbn_normalized::sequence sequence;
        dbn_normalized::bid_ask_pair bid_ask_pair;
    };

    dbn_normalized::record_header header = {record_length((sizeof(dbn_normalized::record_header) + sizeof(fields_type)) / 4), rtype::enum_type::bbo_1_second, {}, {}, {}};

    fields_type fields;

    // parse method
    static bbo_msg* parse(std::byte* buffer) {
        return reinterpret_cast<bbo_msg*>(buffer);
    }

    // parse method const
    static const bbo_msg* parse(const std::byte* buffer) {
        return reinterpret_cast<const bbo_msg*>(buffer);
    }

};

// layout verification
static_assert(offsetof(bbo_msg::fields_type, price) == 0, "unexpected offset of bbo_msg::fields_type::price");
static_assert(offsetof(bbo_msg::fields_type, size) == 8, "unexpected offset of bbo_msg::fields_type::size");
static_assert(offsetof(bbo_msg::fields_type, reserved_1) == 12, "unexpected offset of bbo_msg::fields_type::reserved_1");
static_assert(offsetof(bbo_msg::fields_type, side) == 13, "unexpected offset of bbo_msg::fields_type::side");
static_assert(offsetof(bbo_msg::fields_type, flags) == 14, "unexpected offset of bbo_msg::fields_type::flags");
static_assert(offsetof(bbo_msg::fields_type, second_reserved_1) == 15, "unexpected offset of bbo_msg::fields_type::second_reserved_1");
static_assert(offsetof(bbo_msg::fields_type, ts_recv) == 16, "unexpected offset of bbo_msg::fields_type::ts_recv");
static_assert(offsetof(bbo_msg::fields_type, reserved_4) == 24, "unexpected offset of bbo_msg::fields_type::reserved_4");
static_assert(offsetof(bbo_msg::fields_type, sequence) == 28, "unexpected offset of bbo_msg::fields_type::sequence");
static_assert(offsetof(bbo_msg::fields_type, bid_ask_pair) == 32, "unexpected offset of bbo_msg::fields_type::bid_ask_pair");
static_assert(sizeof(bbo_msg::fields_type) == 64, "unexpected sizeof bbo_msg::fields_type");
static_assert(sizeof(bbo_msg) == sizeof(dbn_normalized::record_header) + 64, "unexpected sizeof bbo_msg");

#pragma pack(pop)
}
