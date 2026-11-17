// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: groups/SettlementValueMdEntry.hpp
#pragma once

#include "../types/MdEntryType.hpp"
#include "../structs/MdEntryPx.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct SettlementValueMdEntry {

    MdEntryType md_entry_type;
    MdEntryPx md_entry_px;

    // parse method
    static SettlementValueMdEntry* parse(std::byte* buffer) {
        return reinterpret_cast<SettlementValueMdEntry*>(buffer);
    }

    // parse method const
    static const SettlementValueMdEntry* parse(const std::byte* buffer) {
        return reinterpret_cast<const SettlementValueMdEntry*>(buffer);
    }
};

#pragma pack(pop)
}
