// Databento.MarketData.Normalized.Dbn.v1: structs/Record.hpp
#pragma once

#include <cstddef>
#include "../structs/RecordHeader.hpp"
#include "../types/TsOutTime.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v1;

#pragma pack(push, 1)

struct record {

    dbn_normalized::record_header record_header;
    dbn_normalized::ts_out_time ts_out_time;

    // parse method
    static record* parse(std::byte* buffer) {
        return reinterpret_cast<record*>(buffer);
    }

    // parse method const
    static const record* parse(const std::byte* buffer) {
        return reinterpret_cast<const record*>(buffer);
    }
};

#pragma pack(pop)
}
