#pragma once

#include "ComplexSeriesIndexMappingMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

namespace pillar_deepfeed = ::nyse::arcaoptions::deepfeed::pillar::v1_2_m;


inline external_count_iterator<complex_series_index_mapping_message_complex_series_index_mapping_leg_entry> read_complex_series_index_mapping_leg(const complex_series_index_mapping_message& msg) {
    return { msg.tail_begin(), msg.fields.no_of_legs.get().value(), msg.tail_end() };
}

}
