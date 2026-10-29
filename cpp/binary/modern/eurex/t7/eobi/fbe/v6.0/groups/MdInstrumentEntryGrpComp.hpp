#pragma once

#include "../types/MdEntryPx.hpp"
#include "../types/MdEntrySize.hpp"
#include "../types/MdEntryType.hpp"
#include "../types/TradeCondition.hpp"
#include "../types/Pad2.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

#pragma pack(push, 1)

struct MdInstrumentEntryGrpComp {

    MdEntryPx md_entry_px;
    MdEntrySize md_entry_size;
    MdEntryType md_entry_type;
    TradeCondition trade_condition;
    Pad2 pad2;

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
