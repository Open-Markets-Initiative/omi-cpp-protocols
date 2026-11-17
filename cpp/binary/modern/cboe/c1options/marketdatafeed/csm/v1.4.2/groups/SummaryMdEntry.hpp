// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: groups/SummaryMdEntry.hpp
#pragma once

#include "../types/MdEntryType.hpp"
#include "../structs/MdEntryPx.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct SummaryMdEntry {

    MdEntryType md_entry_type;
    MdEntryPx md_entry_px;

    // parse method
    static SummaryMdEntry* parse(std::byte* buffer) {
        return reinterpret_cast<SummaryMdEntry*>(buffer);
    }

    // parse method const
    static const SummaryMdEntry* parse(const std::byte* buffer) {
        return reinterpret_cast<const SummaryMdEntry*>(buffer);
    }
};

#pragma pack(pop)
}
