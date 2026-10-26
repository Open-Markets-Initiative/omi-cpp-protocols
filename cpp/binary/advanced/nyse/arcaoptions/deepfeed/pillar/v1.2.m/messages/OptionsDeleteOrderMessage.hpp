#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/OrderId.hpp"
#include "../types/Reserved1.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

namespace pillar_deepfeed = ::nyse::arcaoptions::deepfeed::pillar::v1_2_m;

#pragma pack(push, 1)

// Options Delete Order Message
struct options_delete_order_message {

    struct fields_type {
        pillar_deepfeed::source_time_ns source_time_ns;
        pillar_deepfeed::series_index series_index;
        pillar_deepfeed::series_seq_num series_seq_num;
        pillar_deepfeed::order_id order_id;
        pillar_deepfeed::reserved_1 reserved_1;
    };

    pillar_deepfeed::message_header header = {std::uint16_t(sizeof(pillar_deepfeed::message_header) + sizeof(fields_type)), message_type::enum_type::options_delete_order_message};

    fields_type fields;

    // parse method
    static options_delete_order_message* parse(std::byte* buffer) {
        return reinterpret_cast<options_delete_order_message*>(buffer);
    }

    // parse method const
    static const options_delete_order_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const options_delete_order_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(options_delete_order_message::fields_type, source_time_ns) == 0, "unexpected offset of options_delete_order_message::fields_type::source_time_ns");
static_assert(offsetof(options_delete_order_message::fields_type, series_index) == 4, "unexpected offset of options_delete_order_message::fields_type::series_index");
static_assert(offsetof(options_delete_order_message::fields_type, series_seq_num) == 8, "unexpected offset of options_delete_order_message::fields_type::series_seq_num");
static_assert(offsetof(options_delete_order_message::fields_type, order_id) == 12, "unexpected offset of options_delete_order_message::fields_type::order_id");
static_assert(offsetof(options_delete_order_message::fields_type, reserved_1) == 20, "unexpected offset of options_delete_order_message::fields_type::reserved_1");
static_assert(sizeof(options_delete_order_message::fields_type) == 21, "unexpected sizeof options_delete_order_message::fields_type");
static_assert(sizeof(options_delete_order_message) == sizeof(pillar_deepfeed::message_header) + 21, "unexpected sizeof options_delete_order_message");

#pragma pack(pop)
}
