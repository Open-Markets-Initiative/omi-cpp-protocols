#pragma once

#include "../types/MdEntryPx.hpp"
#include "../types/MdEntrySize.hpp"
#include "../types/MdEntryType.hpp"
#include "../types/Pad3.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

#pragma pack(push, 1)

struct MdInstrumentEntryGrpComp {

    MdEntryPx md_entry_px;
    MdEntrySize md_entry_size;
    MdEntryType md_entry_type;
    Pad3 pad3;

    // parse method
    static MdInstrumentEntryGrpComp* parse(std::byte* buffer) {
        return reinterpret_cast<MdInstrumentEntryGrpComp*>(buffer);
    }

    // parse method const
    static const MdInstrumentEntryGrpComp* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdInstrumentEntryGrpComp*>(buffer);
    }
};

#pragma pack(pop)
}
