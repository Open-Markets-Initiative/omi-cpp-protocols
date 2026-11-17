// Databento.MarketData.Normalized.Dbn.v1: structs/Record.hpp
#pragma once

#include "../structs/RecordHeader.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

#pragma pack(push, 1)

struct Record {

    RecordHeader record_header;

    // parse method
    static Record* parse(std::byte* buffer) {
        return reinterpret_cast<Record*>(buffer);
    }

    // parse method const
    static const Record* parse(const std::byte* buffer) {
        return reinterpret_cast<const Record*>(buffer);
    }
};

#pragma pack(pop)
}
