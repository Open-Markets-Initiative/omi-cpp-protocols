#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/SeriesStatus.hpp"
#include "../types/MarketState.hpp"
#include "../types/OptionsStatusHaltCondition.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

namespace pillar_deepfeed = ::nyse::arcaoptions::deepfeed::pillar::v1_2_m;

#pragma pack(push, 1)

// Options Status Message
struct options_status_message {

    struct fields_type {
        pillar_deepfeed::source_time source_time;
        pillar_deepfeed::source_time_ns source_time_ns;
        pillar_deepfeed::series_index series_index;
        pillar_deepfeed::series_seq_num series_seq_num;
        pillar_deepfeed::series_status series_status;
        pillar_deepfeed::market_state market_state;
        pillar_deepfeed::options_status_halt_condition options_status_halt_condition;
    };

    pillar_deepfeed::message_header header = {std::uint16_t(sizeof(pillar_deepfeed::message_header) + sizeof(fields_type)), message_type::enum_type::options_status_message};

    fields_type fields;

    // parse method
    static options_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<options_status_message*>(buffer);
    }

    // parse method const
    static const options_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const options_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(options_status_message::fields_type, source_time) == 0, "unexpected offset of options_status_message::fields_type::source_time");
static_assert(offsetof(options_status_message::fields_type, source_time_ns) == 4, "unexpected offset of options_status_message::fields_type::source_time_ns");
static_assert(offsetof(options_status_message::fields_type, series_index) == 8, "unexpected offset of options_status_message::fields_type::series_index");
static_assert(offsetof(options_status_message::fields_type, series_seq_num) == 12, "unexpected offset of options_status_message::fields_type::series_seq_num");
static_assert(offsetof(options_status_message::fields_type, series_status) == 16, "unexpected offset of options_status_message::fields_type::series_status");
static_assert(offsetof(options_status_message::fields_type, market_state) == 17, "unexpected offset of options_status_message::fields_type::market_state");
static_assert(offsetof(options_status_message::fields_type, options_status_halt_condition) == 18, "unexpected offset of options_status_message::fields_type::options_status_halt_condition");
static_assert(sizeof(options_status_message::fields_type) == 19, "unexpected sizeof options_status_message::fields_type");
static_assert(sizeof(options_status_message) == sizeof(pillar_deepfeed::message_header) + 19, "unexpected sizeof options_status_message");

#pragma pack(pop)
}
