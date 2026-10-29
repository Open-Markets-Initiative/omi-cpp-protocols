#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../structs/TradeCondition.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

namespace pillar_topfeed = ::nyse::arcaoptions::topfeed::pillar::v1_2_c;

#pragma pack(push, 1)

// Options Trade Message
struct options_trade_message {

    struct fields_type {
        pillar_topfeed::source_time source_time;
        pillar_topfeed::source_time_ns source_time_ns;
        pillar_topfeed::series_index series_index;
        pillar_topfeed::series_seq_num series_seq_num;
        pillar_topfeed::trade_id trade_id;
        pillar_topfeed::price price;
        pillar_topfeed::volume volume;
        pillar_topfeed::trade_condition trade_condition;
    };

    pillar_topfeed::message_header header = {std::uint16_t(sizeof(pillar_topfeed::message_header) + sizeof(fields_type)), message_type::enum_type::options_trade_message};

    fields_type fields;

    // parse method
    static options_trade_message* parse(std::byte* buffer) {
        return reinterpret_cast<options_trade_message*>(buffer);
    }

    // parse method const
    static const options_trade_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const options_trade_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(options_trade_message::fields_type, source_time) == 0, "unexpected offset of options_trade_message::fields_type::source_time");
static_assert(offsetof(options_trade_message::fields_type, source_time_ns) == 4, "unexpected offset of options_trade_message::fields_type::source_time_ns");
static_assert(offsetof(options_trade_message::fields_type, series_index) == 8, "unexpected offset of options_trade_message::fields_type::series_index");
static_assert(offsetof(options_trade_message::fields_type, series_seq_num) == 12, "unexpected offset of options_trade_message::fields_type::series_seq_num");
static_assert(offsetof(options_trade_message::fields_type, trade_id) == 16, "unexpected offset of options_trade_message::fields_type::trade_id");
static_assert(offsetof(options_trade_message::fields_type, price) == 20, "unexpected offset of options_trade_message::fields_type::price");
static_assert(offsetof(options_trade_message::fields_type, volume) == 24, "unexpected offset of options_trade_message::fields_type::volume");
static_assert(offsetof(options_trade_message::fields_type, trade_condition) == 28, "unexpected offset of options_trade_message::fields_type::trade_condition");
static_assert(sizeof(options_trade_message::fields_type) == 32, "unexpected sizeof options_trade_message::fields_type");
static_assert(sizeof(options_trade_message) == sizeof(pillar_topfeed::message_header) + 32, "unexpected sizeof options_trade_message");

#pragma pack(pop)
}
