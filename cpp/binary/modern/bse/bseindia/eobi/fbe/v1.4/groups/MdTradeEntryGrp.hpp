#pragma once

#include "../types/MdEntryPx.hpp"
#include "../types/MdEntrySize.hpp"
#include "../types/MdEntryType.hpp"
#include "../types/Pad7.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

struct MdTradeEntryGrp {

    MdEntryPx md_entry_px;
    MdEntrySize md_entry_size;
    MdEntryType md_entry_type;
    Pad7 pad_7;

    // parse method
    static MdTradeEntryGrp* parse(std::byte* buffer) {
        return reinterpret_cast<MdTradeEntryGrp*>(buffer);
    }

    // parse method const
    static const MdTradeEntryGrp* parse(const std::byte* buffer) {
        return reinterpret_cast<const MdTradeEntryGrp*>(buffer);
    }
};

#pragma pack(pop)
}
