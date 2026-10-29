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

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

namespace pillar_topfeed = ::nyse::arcaoptions::topfeed::pillar::v1_2_c;

#pragma pack(push, 1)

// Outright Series Summary Message
struct outright_series_summary_message {

    struct fields_type {
        pillar_topfeed::source_time source_time;
        pillar_topfeed::source_time_ns source_time_ns;
        pillar_topfeed::series_index series_index;
        pillar_topfeed::high_price high_price;
        pillar_topfeed::low_price low_price;
        pillar_topfeed::open open;
        pillar_topfeed::close close;
        pillar_topfeed::total_volume total_volume;
    };

    pillar_topfeed::message_header header = {std::uint16_t(sizeof(pillar_topfeed::message_header) + sizeof(fields_type)), message_type::enum_type::outright_series_summary_message};

    fields_type fields;

    // parse method
    static outright_series_summary_message* parse(std::byte* buffer) {
        return reinterpret_cast<outright_series_summary_message*>(buffer);
    }

    // parse method const
    static const outright_series_summary_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const outright_series_summary_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(outright_series_summary_message::fields_type, source_time) == 0, "unexpected offset of outright_series_summary_message::fields_type::source_time");
static_assert(offsetof(outright_series_summary_message::fields_type, source_time_ns) == 4, "unexpected offset of outright_series_summary_message::fields_type::source_time_ns");
static_assert(offsetof(outright_series_summary_message::fields_type, series_index) == 8, "unexpected offset of outright_series_summary_message::fields_type::series_index");
static_assert(offsetof(outright_series_summary_message::fields_type, high_price) == 12, "unexpected offset of outright_series_summary_message::fields_type::high_price");
static_assert(offsetof(outright_series_summary_message::fields_type, low_price) == 16, "unexpected offset of outright_series_summary_message::fields_type::low_price");
static_assert(offsetof(outright_series_summary_message::fields_type, open) == 20, "unexpected offset of outright_series_summary_message::fields_type::open");
static_assert(offsetof(outright_series_summary_message::fields_type, close) == 24, "unexpected offset of outright_series_summary_message::fields_type::close");
static_assert(offsetof(outright_series_summary_message::fields_type, total_volume) == 28, "unexpected offset of outright_series_summary_message::fields_type::total_volume");
static_assert(sizeof(outright_series_summary_message::fields_type) == 32, "unexpected sizeof outright_series_summary_message::fields_type");
static_assert(sizeof(outright_series_summary_message) == sizeof(pillar_topfeed::message_header) + 32, "unexpected sizeof outright_series_summary_message");

#pragma pack(pop)
}
