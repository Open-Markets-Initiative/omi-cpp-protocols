#pragma once

#include <cstddef>
#include "../types/RelatedSecurityId.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v13_0;

#pragma pack(push, 1)

struct related_instrument_grp_comp {

    fbe_eobi::related_security_id related_security_id;

    // parse method
    static related_instrument_grp_comp* parse(std::byte* buffer) {
        return reinterpret_cast<related_instrument_grp_comp*>(buffer);
    }

    // parse method const
    static const related_instrument_grp_comp* parse(const std::byte* buffer) {
        return reinterpret_cast<const related_instrument_grp_comp*>(buffer);
    }
};

// layout verification
static_assert(offsetof(related_instrument_grp_comp, related_security_id) == 0, "unexpected offset of related_instrument_grp_comp::related_security_id");
static_assert(sizeof(related_instrument_grp_comp) == 8, "unexpected sizeof related_instrument_grp_comp");

#pragma pack(pop)
}
