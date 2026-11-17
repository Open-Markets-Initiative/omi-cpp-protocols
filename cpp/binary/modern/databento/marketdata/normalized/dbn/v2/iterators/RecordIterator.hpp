// Databento.MarketData.Normalized.Dbn.v2: iterators/RecordIterator.hpp
#pragma once

#include "../definitions.hpp"

namespace databento::marketdata::normalized::dbn::v2 {
// RecordIterator
struct RecordIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const Record* record = nullptr;
    std::uint8_t rtype = 0;
    std::uint8_t record_length = 0;
    const std::byte* message = nullptr;

    // initialize over reassembled byte stream
    void initialize(const std::byte* data, std::size_t bytes) {
        current = data;
        end = data + bytes;

        record = nullptr;
        message = nullptr;
        rtype = 0;
        record_length = 0;
    }

    // next reassembled packet
    bool next() {

        if (current >= end) {
            return false;
        }

        if (current + sizeof(Record) > end) {
            return false;
        }

        record = Record::parse(current);
        message = current + sizeof(Record);

        rtype = record->record_header.rtype.get();
        record_length = record->record_header.record_length.get();

        current += record_length * 4;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        record = nullptr;
        message = nullptr;
        rtype = 0;
        record_length = 0;
    }
};
}
