#pragma once

#include <cstddef>
#include "../types/RecordLength.hpp"
#include "../types/Rtype.hpp"
#include "../types/PublisherId.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/TsEvent.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v1;

#pragma pack(push, 1)

struct record_header {

    dbn_normalized::record_length record_length;
    dbn_normalized::rtype rtype;
    dbn_normalized::publisher_id publisher_id;
    dbn_normalized::instrument_id instrument_id;
    dbn_normalized::ts_event ts_event;

    // parse method
    static record_header* parse(std::byte* buffer) {
        return reinterpret_cast<record_header*>(buffer);
    }

    // parse method const
    static const record_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const record_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(record_header, record_length) == 0, "unexpected offset of record_header::record_length");
static_assert(offsetof(record_header, rtype) == 1, "unexpected offset of record_header::rtype");
static_assert(offsetof(record_header, publisher_id) == 2, "unexpected offset of record_header::publisher_id");
static_assert(offsetof(record_header, instrument_id) == 4, "unexpected offset of record_header::instrument_id");
static_assert(offsetof(record_header, ts_event) == 8, "unexpected offset of record_header::ts_event");
static_assert(sizeof(record_header) == 16, "unexpected sizeof record_header");

#pragma pack(pop)
}
