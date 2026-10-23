#pragma once

#include <cstddef>
#include "../types/MdEntryPx.hpp"
#include "../types/MdEntrySize.hpp"
#include "../types/MdEntryType.hpp"
#include "../types/Pad7.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v15_0;

#pragma pack(push, 1)

struct md_trade_entry_grp_comp {

    fbe_eobi::md_entry_px md_entry_px;
    fbe_eobi::md_entry_size md_entry_size;
    fbe_eobi::md_entry_type md_entry_type;
    fbe_eobi::pad7 pad7;

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
static_assert(offsetof(md_trade_entry_grp_comp, md_entry_type) == 16, "unexpected offset of md_trade_entry_grp_comp::md_entry_type");
static_assert(offsetof(md_trade_entry_grp_comp, pad7) == 17, "unexpected offset of md_trade_entry_grp_comp::pad7");
static_assert(sizeof(md_trade_entry_grp_comp) == 24, "unexpected sizeof md_trade_entry_grp_comp");

#pragma pack(pop)
}
