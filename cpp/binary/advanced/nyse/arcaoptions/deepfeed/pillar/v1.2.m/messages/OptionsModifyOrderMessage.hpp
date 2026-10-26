#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/OrderId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/PositionChange.hpp"
#include "../types/Side.hpp"
#include "../types/CustIndicator.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

namespace pillar_deepfeed = ::nyse::arcaoptions::deepfeed::pillar::v1_2_m;

#pragma pack(push, 1)

// Options Modify Order Message
struct options_modify_order_message {

    struct fields_type {
        pillar_deepfeed::source_time_ns source_time_ns;
        pillar_deepfeed::series_index series_index;
        pillar_deepfeed::series_seq_num series_seq_num;
        pillar_deepfeed::order_id order_id;
        pillar_deepfeed::price price;
        pillar_deepfeed::volume volume;
        pillar_deepfeed::position_change position_change;
        pillar_deepfeed::side side;
        pillar_deepfeed::cust_indicator cust_indicator;
    };

    pillar_deepfeed::message_header header = {std::uint16_t(sizeof(pillar_deepfeed::message_header) + sizeof(fields_type)), message_type::enum_type::options_modify_order_message};

    fields_type fields;

    // parse method
    static options_modify_order_message* parse(std::byte* buffer) {
        return reinterpret_cast<options_modify_order_message*>(buffer);
    }

    // parse method const
    static const options_modify_order_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const options_modify_order_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(options_modify_order_message::fields_type, source_time_ns) == 0, "unexpected offset of options_modify_order_message::fields_type::source_time_ns");
static_assert(offsetof(options_modify_order_message::fields_type, series_index) == 4, "unexpected offset of options_modify_order_message::fields_type::series_index");
static_assert(offsetof(options_modify_order_message::fields_type, series_seq_num) == 8, "unexpected offset of options_modify_order_message::fields_type::series_seq_num");
static_assert(offsetof(options_modify_order_message::fields_type, order_id) == 12, "unexpected offset of options_modify_order_message::fields_type::order_id");
static_assert(offsetof(options_modify_order_message::fields_type, price) == 20, "unexpected offset of options_modify_order_message::fields_type::price");
static_assert(offsetof(options_modify_order_message::fields_type, volume) == 24, "unexpected offset of options_modify_order_message::fields_type::volume");
static_assert(offsetof(options_modify_order_message::fields_type, position_change) == 28, "unexpected offset of options_modify_order_message::fields_type::position_change");
static_assert(offsetof(options_modify_order_message::fields_type, side) == 29, "unexpected offset of options_modify_order_message::fields_type::side");
static_assert(offsetof(options_modify_order_message::fields_type, cust_indicator) == 30, "unexpected offset of options_modify_order_message::fields_type::cust_indicator");
static_assert(sizeof(options_modify_order_message::fields_type) == 31, "unexpected sizeof options_modify_order_message::fields_type");
static_assert(sizeof(options_modify_order_message) == sizeof(pillar_deepfeed::message_header) + 31, "unexpected sizeof options_modify_order_message");

#pragma pack(pop)
}
