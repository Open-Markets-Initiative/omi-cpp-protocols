#pragma once

#include "../types/MdEntryPx.hpp"
#include "../types/MdEntrySize.hpp"
#include "../types/MdEntryType.hpp"
#include "../types/Pad3.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

#pragma pack(push, 1)

struct MdTradeEntryGrpComp {

    MdEntryPx md_entry_px;
    MdEntrySize md_entry_size;
    MdEntryType md_entry_type;
    Pad3 pad3;

    // parse method
    static MdTradeEntryGrpComp* parse(std::byte* buffer) {
        return reinterpret_cast<MdTradeEntryGrpComp*>(buffer);
    }

    // parse method const
    static const MdTradeEntryGrpComp* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdTradeEntryGrpComp*>(buffer);
    }
};

#pragma pack(pop)
}
