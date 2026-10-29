#pragma once

#include <cstddef>
#include "../types/MdEntryPxExponent.hpp"
#include "../types/MdEntryPxMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

#pragma pack(push, 1)

struct md_entry_px {

    csm_marketdatafeed::md_entry_px_exponent md_entry_px_exponent;
    csm_marketdatafeed::md_entry_px_mantissa md_entry_px_mantissa;

    // parse method
    static md_entry_px* parse(std::byte* buffer) {
        return reinterpret_cast<md_entry_px*>(buffer);
    }

    // parse method const
    static const md_entry_px* parse(const std::byte* buffer) {
        return reinterpret_cast<const md_entry_px*>(buffer);
    }
};

// layout verification
static_assert(offsetof(md_entry_px, md_entry_px_exponent) == 0, "unexpected offset of md_entry_px::md_entry_px_exponent");
static_assert(offsetof(md_entry_px, md_entry_px_mantissa) == 1, "unexpected offset of md_entry_px::md_entry_px_mantissa");
static_assert(sizeof(md_entry_px) == 5, "unexpected sizeof md_entry_px");

#pragma pack(pop)
}
