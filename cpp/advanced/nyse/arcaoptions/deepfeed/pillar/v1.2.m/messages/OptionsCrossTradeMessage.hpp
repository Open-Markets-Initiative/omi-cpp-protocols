#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/CrossId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/CrossType.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

namespace pillar_deepfeed = ::nyse::arcaoptions::deepfeed::pillar::v1_2_m;

#pragma pack(push, 1)

// Options Cross Trade Message
struct options_cross_trade_message {

    struct fields_type {
        pillar_deepfeed::source_time_ns source_time_ns;
        pillar_deepfeed::series_index series_index;
        pillar_deepfeed::series_seq_num series_seq_num;
        pillar_deepfeed::cross_id cross_id;
        pillar_deepfeed::price price;
        pillar_deepfeed::volume volume;
        pillar_deepfeed::cross_type cross_type;
    };

    pillar_deepfeed::message_header header = {std::uint16_t(sizeof(pillar_deepfeed::message_header) + sizeof(fields_type)), message_type::enum_type::options_cross_trade_message};

    fields_type fields;

    // parse method
    static options_cross_trade_message* parse(std::byte* buffer) {
        return reinterpret_cast<options_cross_trade_message*>(buffer);
    }

    // parse method const
    static const options_cross_trade_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const options_cross_trade_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(options_cross_trade_message::fields_type, source_time_ns) == 0, "unexpected offset of options_cross_trade_message::fields_type::source_time_ns");
static_assert(offsetof(options_cross_trade_message::fields_type, series_index) == 4, "unexpected offset of options_cross_trade_message::fields_type::series_index");
static_assert(offsetof(options_cross_trade_message::fields_type, series_seq_num) == 8, "unexpected offset of options_cross_trade_message::fields_type::series_seq_num");
static_assert(offsetof(options_cross_trade_message::fields_type, cross_id) == 12, "unexpected offset of options_cross_trade_message::fields_type::cross_id");
static_assert(offsetof(options_cross_trade_message::fields_type, price) == 16, "unexpected offset of options_cross_trade_message::fields_type::price");
static_assert(offsetof(options_cross_trade_message::fields_type, volume) == 20, "unexpected offset of options_cross_trade_message::fields_type::volume");
static_assert(offsetof(options_cross_trade_message::fields_type, cross_type) == 24, "unexpected offset of options_cross_trade_message::fields_type::cross_type");
static_assert(sizeof(options_cross_trade_message::fields_type) == 25, "unexpected sizeof options_cross_trade_message::fields_type");
static_assert(sizeof(options_cross_trade_message) == sizeof(pillar_deepfeed::message_header) + 25, "unexpected sizeof options_cross_trade_message");

#pragma pack(pop)
}
