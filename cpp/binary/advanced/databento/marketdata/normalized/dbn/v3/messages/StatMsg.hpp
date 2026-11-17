// Databento.MarketData.Normalized.Dbn.v3: messages/StatMsg.hpp
#pragma once

#include <cstddef>
#include "../structs/RecordHeader.hpp"
#include "../types/TsRecv.hpp"
#include "../types/TsRef.hpp"
#include "../types/Price.hpp"
#include "../types/Quantity.hpp"
#include "../types/Sequence.hpp"
#include "../types/TsInDelta.hpp"
#include "../types/StatType.hpp"
#include "../types/Channel.hpp"
#include "../types/UpdateAction.hpp"
#include "../types/StatFlags.hpp"
#include "../types/Reserved18.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v3;

#pragma pack(push, 1)

// Stat Msg
struct stat_msg {

    struct fields_type {
        dbn_normalized::ts_recv ts_recv;
        dbn_normalized::ts_ref ts_ref;
        dbn_normalized::price price;
        dbn_normalized::quantity quantity;
        dbn_normalized::sequence sequence;
        dbn_normalized::ts_in_delta ts_in_delta;
        dbn_normalized::stat_type stat_type;
        dbn_normalized::channel channel;
        dbn_normalized::update_action update_action;
        dbn_normalized::stat_flags stat_flags;
        dbn_normalized::reserved_18 reserved_18;
    };

    dbn_normalized::record_header header = {record_length((sizeof(dbn_normalized::record_header) + sizeof(fields_type)) / 4), rtype::enum_type::statistics, {}, {}, {}};

    fields_type fields;

    // parse method
    static stat_msg* parse(std::byte* buffer) {
        return reinterpret_cast<stat_msg*>(buffer);
    }

    // parse method const
    static const stat_msg* parse(const std::byte* buffer) {
        return reinterpret_cast<const stat_msg*>(buffer);
    }

};

// layout verification
static_assert(offsetof(stat_msg::fields_type, ts_recv) == 0, "unexpected offset of stat_msg::fields_type::ts_recv");
static_assert(offsetof(stat_msg::fields_type, ts_ref) == 8, "unexpected offset of stat_msg::fields_type::ts_ref");
static_assert(offsetof(stat_msg::fields_type, price) == 16, "unexpected offset of stat_msg::fields_type::price");
static_assert(offsetof(stat_msg::fields_type, quantity) == 24, "unexpected offset of stat_msg::fields_type::quantity");
static_assert(offsetof(stat_msg::fields_type, sequence) == 32, "unexpected offset of stat_msg::fields_type::sequence");
static_assert(offsetof(stat_msg::fields_type, ts_in_delta) == 36, "unexpected offset of stat_msg::fields_type::ts_in_delta");
static_assert(offsetof(stat_msg::fields_type, stat_type) == 40, "unexpected offset of stat_msg::fields_type::stat_type");
static_assert(offsetof(stat_msg::fields_type, channel) == 42, "unexpected offset of stat_msg::fields_type::channel");
static_assert(offsetof(stat_msg::fields_type, update_action) == 44, "unexpected offset of stat_msg::fields_type::update_action");
static_assert(offsetof(stat_msg::fields_type, stat_flags) == 45, "unexpected offset of stat_msg::fields_type::stat_flags");
static_assert(offsetof(stat_msg::fields_type, reserved_18) == 46, "unexpected offset of stat_msg::fields_type::reserved_18");
static_assert(sizeof(stat_msg::fields_type) == 64, "unexpected sizeof stat_msg::fields_type");
static_assert(sizeof(stat_msg) == sizeof(dbn_normalized::record_header) + 64, "unexpected sizeof stat_msg");

#pragma pack(pop)
}
