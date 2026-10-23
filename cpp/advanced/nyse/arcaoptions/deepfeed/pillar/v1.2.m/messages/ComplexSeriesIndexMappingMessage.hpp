#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/MarketId.hpp"
#include "../types/SystemId.hpp"
#include "../types/NoOfLegs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/LegSide.hpp"
#include "../types/LegSecurityType.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

namespace pillar_deepfeed = ::nyse::arcaoptions::deepfeed::pillar::v1_2_m;

#pragma pack(push, 1)
struct complex_series_index_mapping_message_complex_series_index_mapping_leg_entry {
    pillar_deepfeed::symbol_index symbol_index;
    pillar_deepfeed::leg_ratio_qty leg_ratio_qty;
    pillar_deepfeed::leg_side leg_side;
    pillar_deepfeed::leg_security_type leg_security_type;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Complex Series Index Mapping Message
struct complex_series_index_mapping_message {

    struct fields_type {
        pillar_deepfeed::series_index series_index;
        pillar_deepfeed::market_id market_id;
        pillar_deepfeed::system_id system_id;
        pillar_deepfeed::no_of_legs no_of_legs;
    };

    pillar_deepfeed::message_header header = {std::uint16_t(sizeof(pillar_deepfeed::message_header) + sizeof(fields_type)), message_type::enum_type::complex_series_index_mapping_message};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(pillar_deepfeed::message_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_size.get().value();
        return sz == sizeof(pillar_deepfeed::message_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + (sz - sizeof(pillar_deepfeed::message_header) - sizeof(fields_type));
    }

    // sequential access to variable-length regions
    external_count_iterator<complex_series_index_mapping_message_complex_series_index_mapping_leg_entry> complex_series_index_mapping_leg() const {
        return { tail_begin(), fields.no_of_legs.get().value(), tail_end() };
    }


    // parse method
    static complex_series_index_mapping_message* parse(std::byte* buffer) {
        return reinterpret_cast<complex_series_index_mapping_message*>(buffer);
    }

    // parse method const
    static const complex_series_index_mapping_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const complex_series_index_mapping_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(complex_series_index_mapping_message::fields_type, series_index) == 0, "unexpected offset of complex_series_index_mapping_message::fields_type::series_index");
static_assert(offsetof(complex_series_index_mapping_message::fields_type, market_id) == 4, "unexpected offset of complex_series_index_mapping_message::fields_type::market_id");
static_assert(offsetof(complex_series_index_mapping_message::fields_type, system_id) == 6, "unexpected offset of complex_series_index_mapping_message::fields_type::system_id");
static_assert(offsetof(complex_series_index_mapping_message::fields_type, no_of_legs) == 7, "unexpected offset of complex_series_index_mapping_message::fields_type::no_of_legs");
static_assert(sizeof(complex_series_index_mapping_message::fields_type) == 9, "unexpected sizeof complex_series_index_mapping_message::fields_type");

#pragma pack(pop)
}

#include "details/ComplexSeriesIndexMappingMessageWriter.hpp"
#include "details/ComplexSeriesIndexMappingMessageReader.hpp"
