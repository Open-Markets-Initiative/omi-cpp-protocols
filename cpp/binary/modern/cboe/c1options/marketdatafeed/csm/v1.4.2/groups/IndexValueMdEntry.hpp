// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: groups/IndexValueMdEntry.hpp
#pragma once

#include "../types/MdEntryType.hpp"
#include "../structs/MdEntryPx.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct IndexValueMdEntry {

    MdEntryType md_entry_type;
    MdEntryPx md_entry_px;

    // parse method
    static IndexValueMdEntry* parse(std::byte* buffer) {
        return reinterpret_cast<IndexValueMdEntry*>(buffer);
    }

    // parse method const
    static const IndexValueMdEntry* parse(const std::byte* buffer) {
        return reinterpret_cast<const IndexValueMdEntry*>(buffer);
    }
};

#pragma pack(pop)
}
