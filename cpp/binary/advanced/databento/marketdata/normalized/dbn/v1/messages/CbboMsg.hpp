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
#include "../types/Reserved8.hpp"
#include "../structs/ConsolidatedBidAskPair.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v1;

#pragma pack(push, 1)

// Cbbo Msg
struct cbbo_msg {

    struct fields_type {
        dbn_normalized::price price;
        dbn_normalized::size_type size;
        dbn_normalized::reserved_1 reserved_1;
        dbn_normalized::side side;
        dbn_normalized::flags flags;
        dbn_normalized::second_reserved_1 second_reserved_1;
        dbn_normalized::ts_recv ts_recv;
        dbn_normalized::reserved_8 reserved_8;
        dbn_normalized::consolidated_bid_ask_pair consolidated_bid_ask_pair;
    };

    dbn_normalized::record_header header = {record_length((sizeof(dbn_normalized::record_header) + sizeof(fields_type)) / 4), rtype::enum_type::consolidated_bbo_1_second, {}, {}, {}};

    fields_type fields;

    // parse method
    static cbbo_msg* parse(std::byte* buffer) {
        return reinterpret_cast<cbbo_msg*>(buffer);
    }

    // parse method const
    static const cbbo_msg* parse(const std::byte* buffer) {
        return reinterpret_cast<const cbbo_msg*>(buffer);
    }

};

// layout verification
static_assert(offsetof(cbbo_msg::fields_type, price) == 0, "unexpected offset of cbbo_msg::fields_type::price");
static_assert(offsetof(cbbo_msg::fields_type, size) == 8, "unexpected offset of cbbo_msg::fields_type::size");
static_assert(offsetof(cbbo_msg::fields_type, reserved_1) == 12, "unexpected offset of cbbo_msg::fields_type::reserved_1");
static_assert(offsetof(cbbo_msg::fields_type, side) == 13, "unexpected offset of cbbo_msg::fields_type::side");
static_assert(offsetof(cbbo_msg::fields_type, flags) == 14, "unexpected offset of cbbo_msg::fields_type::flags");
static_assert(offsetof(cbbo_msg::fields_type, second_reserved_1) == 15, "unexpected offset of cbbo_msg::fields_type::second_reserved_1");
static_assert(offsetof(cbbo_msg::fields_type, ts_recv) == 16, "unexpected offset of cbbo_msg::fields_type::ts_recv");
static_assert(offsetof(cbbo_msg::fields_type, reserved_8) == 24, "unexpected offset of cbbo_msg::fields_type::reserved_8");
static_assert(offsetof(cbbo_msg::fields_type, consolidated_bid_ask_pair) == 32, "unexpected offset of cbbo_msg::fields_type::consolidated_bid_ask_pair");
static_assert(sizeof(cbbo_msg::fields_type) == 64, "unexpected sizeof cbbo_msg::fields_type");
static_assert(sizeof(cbbo_msg) == sizeof(dbn_normalized::record_header) + 64, "unexpected sizeof cbbo_msg");

#pragma pack(pop)
}
