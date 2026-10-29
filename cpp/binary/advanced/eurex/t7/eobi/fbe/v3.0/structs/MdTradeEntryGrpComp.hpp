#pragma once

#include <cstddef>
#include "../types/MdEntryPx.hpp"
#include "../types/MdEntrySize.hpp"
#include "../types/MdEntryType.hpp"
#include "../types/Pad3.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v3_0;

#pragma pack(push, 1)

struct md_trade_entry_grp_comp {

    fbe_eobi::md_entry_px md_entry_px;
    fbe_eobi::md_entry_size md_entry_size;
    fbe_eobi::md_entry_type md_entry_type;
    fbe_eobi::pad3 pad3;

    // parse method
    static md_trade_entry_grp_comp* parse(std::byte* buffer) {
        return reinterpret_cast<md_trade_entry_grp_comp*>(buffer);
    }

    // parse method const
    static const md_trade_entry_grp_comp* parse(const std::byte* buffer) {
        return reinterpret_cast<const md_trade_entry_grp_comp*>(buffer);
    }
};

// layout verification
static_assert(offsetof(md_trade_entry_grp_comp, md_entry_px) == 0, "unexpected offset of md_trade_entry_grp_comp::md_entry_px");
static_assert(offsetof(md_trade_entry_grp_comp, md_entry_size) == 8, "unexpected offset of md_trade_entry_grp_comp::md_entry_size");
static_assert(offsetof(md_trade_entry_grp_comp, md_entry_type) == 12, "unexpected offset of md_trade_entry_grp_comp::md_entry_type");
static_assert(offsetof(md_trade_entry_grp_comp, pad3) == 13, "unexpected offset of md_trade_entry_grp_comp::pad3");
static_assert(sizeof(md_trade_entry_grp_comp) == 16, "unexpected sizeof md_trade_entry_grp_comp");

#pragma pack(pop)
}
