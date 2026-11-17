// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: groups/TickerMdEntry.hpp
#pragma once

#include "../types/MdEntryType.hpp"
#include "../structs/MdEntryPx.hpp"
#include "../types/MdEntrySize.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct TickerMdEntry {

    MdEntryType md_entry_type;
    MdEntryPx md_entry_px;
    MdEntrySize md_entry_size;

    // parse method
    static TickerMdEntry* parse(std::byte* buffer) {
        return reinterpret_cast<TickerMdEntry*>(buffer);
    }

    // parse method const
    static const TickerMdEntry* parse(const std::byte* buffer) {
        return reinterpret_cast<const TickerMdEntry*>(buffer);
    }
};

#pragma pack(pop)
}
