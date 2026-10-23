#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/HighPrice.hpp"
#include "../types/LowPrice.hpp"
#include "../types/Open.hpp"
#include "../types/Close.hpp"
#include "../types/TotalVolume.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

namespace pillar_deepfeed = ::nyse::arcaoptions::deepfeed::pillar::v1_2_m;

#pragma pack(push, 1)

// Options Outright Series Summary Message
struct options_outright_series_summary_message {

    struct fields_type {
        pillar_deepfeed::source_time source_time;
        pillar_deepfeed::source_time_ns source_time_ns;
        pillar_deepfeed::series_index series_index;
        pillar_deepfeed::high_price high_price;
        pillar_deepfeed::low_price low_price;
        pillar_deepfeed::open open;
        pillar_deepfeed::close close;
        pillar_deepfeed::total_volume total_volume;
    };

    pillar_deepfeed::message_header header = {std::uint16_t(sizeof(pillar_deepfeed::message_header) + sizeof(fields_type)), message_type::enum_type::options_outright_series_summary_message};

    fields_type fields;

    // parse method
    static options_outright_series_summary_message* parse(std::byte* buffer) {
        return reinterpret_cast<options_outright_series_summary_message*>(buffer);
    }

    // parse method const
    static const options_outright_series_summary_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const options_outright_series_summary_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(options_outright_series_summary_message::fields_type, source_time) == 0, "unexpected offset of options_outright_series_summary_message::fields_type::source_time");
static_assert(offsetof(options_outright_series_summary_message::fields_type, source_time_ns) == 4, "unexpected offset of options_outright_series_summary_message::fields_type::source_time_ns");
static_assert(offsetof(options_outright_series_summary_message::fields_type, series_index) == 8, "unexpected offset of options_outright_series_summary_message::fields_type::series_index");
static_assert(offsetof(options_outright_series_summary_message::fields_type, high_price) == 12, "unexpected offset of options_outright_series_summary_message::fields_type::high_price");
static_assert(offsetof(options_outright_series_summary_message::fields_type, low_price) == 16, "unexpected offset of options_outright_series_summary_message::fields_type::low_price");
static_assert(offsetof(options_outright_series_summary_message::fields_type, open) == 20, "unexpected offset of options_outright_series_summary_message::fields_type::open");
static_assert(offsetof(options_outright_series_summary_message::fields_type, close) == 24, "unexpected offset of options_outright_series_summary_message::fields_type::close");
static_assert(offsetof(options_outright_series_summary_message::fields_type, total_volume) == 28, "unexpected offset of options_outright_series_summary_message::fields_type::total_volume");
static_assert(sizeof(options_outright_series_summary_message::fields_type) == 32, "unexpected sizeof options_outright_series_summary_message::fields_type");
static_assert(sizeof(options_outright_series_summary_message) == sizeof(pillar_deepfeed::message_header) + 32, "unexpected sizeof options_outright_series_summary_message");

#pragma pack(pop)
}
