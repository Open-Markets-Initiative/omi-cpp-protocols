#pragma once

#include <cstddef>
#include "../types/MdEntryPx.hpp"
#include "../types/MdEntrySize.hpp"
#include "../types/MdEntryType.hpp"
#include "../types/Pad7.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

namespace fbe_eobi = ::bse::bseindia::eobi::fbe::v1_4;

#pragma pack(push, 1)

struct md_instrument_entry_grp {

    fbe_eobi::md_entry_px md_entry_px;
    fbe_eobi::md_entry_size md_entry_size;
    fbe_eobi::md_entry_type md_entry_type;
    fbe_eobi::pad_7 pad_7;

    // parse method
    static md_instrument_entry_grp* parse(std::byte* buffer) {
        return reinterpret_cast<md_instrument_entry_grp*>(buffer);
    }

    // parse method const
    static const md_instrument_entry_grp* parse(const std::byte* buffer) {
        return reinterpret_cast<const md_instrument_entry_grp*>(buffer);
    }
};

// layout verification
static_assert(offsetof(md_instrument_entry_grp, md_entry_px) == 0, "unexpected offset of md_instrument_entry_grp::md_entry_px");
static_assert(offsetof(md_instrument_entry_grp, md_entry_size) == 8, "unexpected offset of md_instrument_entry_grp::md_entry_size");
static_assert(offsetof(md_instrument_entry_grp, md_entry_type) == 16, "unexpected offset of md_instrument_entry_grp::md_entry_type");
static_assert(offsetof(md_instrument_entry_grp, pad_7) == 17, "unexpected offset of md_instrument_entry_grp::pad_7");
static_assert(sizeof(md_instrument_entry_grp) == 24, "unexpected sizeof md_instrument_entry_grp");

#pragma pack(pop)
}
