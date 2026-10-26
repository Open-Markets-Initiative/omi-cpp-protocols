#pragma once

#include "../definitions.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {
// ComplexSeriesIndexMappingLegIterator
struct ComplexSeriesIndexMappingLegIterator {

    const std::byte* current = nullptr;

    const ComplexSeriesIndexMappingMessage* complex_series_index_mapping_message = nullptr;

    std::uint16_t no_of_legs = 0;
    std::uint16_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {

        current = data;

        complex_series_index_mapping_message = ComplexSeriesIndexMappingMessage::parse(current);
        current += sizeof(ComplexSeriesIndexMappingMessage);

        no_of_legs = complex_series_index_mapping_message->no_of_legs.get();
        entry_index = 0;
        entry = nullptr;
    }

    // next entry
    bool next() {

        if (entry_index >= no_of_legs) {
            return false;
        }

        entry = current;
        entry_index++;

        return true;
    }

    // advance past processed entry
    void advance(std::size_t bytes) {
        current += bytes;
    }

    // reset iterator
    void reset() {
        current = nullptr;

        complex_series_index_mapping_message = nullptr;

        no_of_legs = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
