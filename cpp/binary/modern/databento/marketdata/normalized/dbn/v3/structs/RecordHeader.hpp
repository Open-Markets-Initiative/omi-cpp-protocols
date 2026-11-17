// Databento.MarketData.Normalized.Dbn.v3: structs/RecordHeader.hpp
#pragma once

#include "../types/RecordLength.hpp"
#include "../types/Rtype.hpp"
#include "../types/PublisherId.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/TsEvent.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

#pragma pack(push, 1)

struct RecordHeader {

    RecordLength record_length;
    Rtype rtype;
    PublisherId publisher_id;
    InstrumentId instrument_id;
    TsEvent ts_event;

    // parse method
    static RecordHeader* parse(std::byte* buffer) {
        return reinterpret_cast<RecordHeader*>(buffer);
    }

    // parse method const
    static const RecordHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const RecordHeader*>(buffer);
    }
};

#pragma pack(pop)
}
