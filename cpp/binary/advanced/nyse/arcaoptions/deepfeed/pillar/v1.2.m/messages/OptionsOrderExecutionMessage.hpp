#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/OrderId.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/PrintableFlag.hpp"
#include "../types/Reserved1.hpp"
#include "../types/TradeCond1.hpp"
#include "../types/Reserved3.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

namespace pillar_deepfeed = ::nyse::arcaoptions::deepfeed::pillar::v1_2_m;

#pragma pack(push, 1)

// Options Order Execution Message
struct options_order_execution_message {

    struct fields_type {
        pillar_deepfeed::source_time_ns source_time_ns;
        pillar_deepfeed::series_index series_index;
        pillar_deepfeed::series_seq_num series_seq_num;
        pillar_deepfeed::order_id order_id;
        pillar_deepfeed::trade_id trade_id;
        pillar_deepfeed::price price;
        pillar_deepfeed::volume volume;
        pillar_deepfeed::printable_flag printable_flag;
        pillar_deepfeed::reserved_1 reserved_1;
        pillar_deepfeed::trade_cond_1 trade_cond_1;
        pillar_deepfeed::reserved_3 reserved_3;
    };

    pillar_deepfeed::message_header header = {std::uint16_t(sizeof(pillar_deepfeed::message_header) + sizeof(fields_type)), message_type::enum_type::options_order_execution_message};

    fields_type fields;

    // parse method
    static options_order_execution_message* parse(std::byte* buffer) {
        return reinterpret_cast<options_order_execution_message*>(buffer);
    }

    // parse method const
    static const options_order_execution_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const options_order_execution_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(options_order_execution_message::fields_type, source_time_ns) == 0, "unexpected offset of options_order_execution_message::fields_type::source_time_ns");
static_assert(offsetof(options_order_execution_message::fields_type, series_index) == 4, "unexpected offset of options_order_execution_message::fields_type::series_index");
static_assert(offsetof(options_order_execution_message::fields_type, series_seq_num) == 8, "unexpected offset of options_order_execution_message::fields_type::series_seq_num");
static_assert(offsetof(options_order_execution_message::fields_type, order_id) == 12, "unexpected offset of options_order_execution_message::fields_type::order_id");
static_assert(offsetof(options_order_execution_message::fields_type, trade_id) == 20, "unexpected offset of options_order_execution_message::fields_type::trade_id");
static_assert(offsetof(options_order_execution_message::fields_type, price) == 24, "unexpected offset of options_order_execution_message::fields_type::price");
static_assert(offsetof(options_order_execution_message::fields_type, volume) == 28, "unexpected offset of options_order_execution_message::fields_type::volume");
static_assert(offsetof(options_order_execution_message::fields_type, printable_flag) == 32, "unexpected offset of options_order_execution_message::fields_type::printable_flag");
static_assert(offsetof(options_order_execution_message::fields_type, reserved_1) == 33, "unexpected offset of options_order_execution_message::fields_type::reserved_1");
static_assert(offsetof(options_order_execution_message::fields_type, trade_cond_1) == 34, "unexpected offset of options_order_execution_message::fields_type::trade_cond_1");
static_assert(offsetof(options_order_execution_message::fields_type, reserved_3) == 35, "unexpected offset of options_order_execution_message::fields_type::reserved_3");
static_assert(sizeof(options_order_execution_message::fields_type) == 38, "unexpected sizeof options_order_execution_message::fields_type");
static_assert(sizeof(options_order_execution_message) == sizeof(pillar_deepfeed::message_header) + 38, "unexpected sizeof options_order_execution_message");

#pragma pack(pop)
}
