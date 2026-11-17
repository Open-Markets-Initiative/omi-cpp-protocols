// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: groups/RecapUpdateMdEntry.hpp
#pragma once

#include "../types/MdEntryType.hpp"
#include "../structs/MdEntryPx.hpp"
#include "../types/MdEntrySize.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct RecapUpdateMdEntry {

    MdEntryType md_entry_type;
    MdEntryPx md_entry_px;
    MdEntrySize md_entry_size;

    // parse method
    static RecapUpdateMdEntry* parse(std::byte* buffer) {
        return reinterpret_cast<RecapUpdateMdEntry*>(buffer);
    }

    // parse method const
    static const RecapUpdateMdEntry* parse(const std::byte* buffer) {
        return reinterpret_cast<const RecapUpdateMdEntry*>(buffer);
    }
};

#pragma pack(pop)
}
