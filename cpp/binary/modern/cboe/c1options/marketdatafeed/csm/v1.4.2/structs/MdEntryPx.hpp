// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/MdEntryPx.hpp
#pragma once

#include "../types/MdEntryPxExponent.hpp"
#include "../types/MdEntryPxMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct MdEntryPx {

    MdEntryPxExponent md_entry_px_exponent;
    MdEntryPxMantissa md_entry_px_mantissa;

    // parse method
    static MdEntryPx* parse(std::byte* buffer) {
        return reinterpret_cast<MdEntryPx*>(buffer);
    }

    // parse method const
    static const MdEntryPx* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdEntryPx*>(buffer);
    }
};

#pragma pack(pop)
}
