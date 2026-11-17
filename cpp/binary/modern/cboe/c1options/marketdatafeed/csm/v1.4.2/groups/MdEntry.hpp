// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: groups/MdEntry.hpp
#pragma once

#include "../types/MdEntryType.hpp"
#include "../structs/MdEntryPx.hpp"
#include "../types/MdEntrySize.hpp"
#include "../types/MdVolumeType.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct MdEntry {

    MdEntryType md_entry_type;
    MdEntryPx md_entry_px;
    MdEntrySize md_entry_size;
    MdVolumeType md_volume_type;

    // parse method
    static MdEntry* parse(std::byte* buffer) {
        return reinterpret_cast<MdEntry*>(buffer);
    }

    // parse method const
    static const MdEntry* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdEntry*>(buffer);
    }
};

#pragma pack(pop)
}
