#pragma once

#include <cstddef>
#include "../types/MdEntryPx.hpp"
#include "../types/MdEntrySize.hpp"
#include "../types/MdEntryType.hpp"
#include "../types/TradeCondition.hpp"
#include "../types/Pad2.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v6_0;

#pragma pack(push, 1)

struct md_instrument_entry_grp_comp {

    fbe_eobi::md_entry_px md_entry_px;
    fbe_eobi::md_entry_size md_entry_size;
    fbe_eobi::md_entry_type md_entry_type;
    fbe_eobi::trade_condition trade_condition;
    fbe_eobi::pad2 pad2;

    // parse method
    static md_instrument_entry_grp_comp* parse(std::byte* buffer) {
        return reinterpret_cast<md_instrument_entry_grp_comp*>(buffer);
    }

    // parse method const
    static const md_instrument_entry_grp_comp* parse(const std::byte* buffer) {
        return reinterpret_cast<const md_instrument_entry_grp_comp*>(buffer);
    }
};

// layout verification
static_assert(offsetof(md_instrument_entry_grp_comp, md_entry_px) == 0, "unexpected offset of md_instrument_entry_grp_comp::md_entry_px");
static_assert(offsetof(md_instrument_entry_grp_comp, md_entry_size) == 8, "unexpected offset of md_instrument_entry_grp_comp::md_entry_size");
static_assert(offsetof(md_instrument_entry_grp_comp, md_entry_type) == 12, "unexpected offset of md_instrument_entry_grp_comp::md_entry_type");
static_assert(offsetof(md_instrument_entry_grp_comp, trade_condition) == 13, "unexpected offset of md_instrument_entry_grp_comp::trade_condition");
static_assert(offsetof(md_instrument_entry_grp_comp, pad2) == 14, "unexpected offset of md_instrument_entry_grp_comp::pad2");
static_assert(sizeof(md_instrument_entry_grp_comp) == 16, "unexpected sizeof md_instrument_entry_grp_comp");

#pragma pack(pop)
}
