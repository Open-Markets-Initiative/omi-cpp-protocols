#pragma once

#include "../types/Timestamp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/ShortSaleRestriction.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

#pragma pack(push, 1)

// RegSHORestrictionMessage
struct RegShoRestrictionMessage {

    Timestamp timestamp;
    SecurityId security_id;
    ShortSaleRestriction short_sale_restriction;

    // parse method
    static RegShoRestrictionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RegShoRestrictionMessage*>(buffer);
    }

    // parse method const
    static const RegShoRestrictionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RegShoRestrictionMessage*>(buffer);
    }
};

#pragma pack(pop)
}
