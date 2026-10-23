#pragma once

#include "../types/BrokenDateGuid.hpp"
#include "../types/BrokenDateSecurityId.hpp"
#include "../types/BrokenDateStart.hpp"
#include "../types/BrokenDateEnd.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct BrokenDatesGroup {

    BrokenDateGuid broken_date_guid;
    BrokenDateSecurityId broken_date_security_id;
    BrokenDateStart broken_date_start;
    BrokenDateEnd broken_date_end;

    // parse method
    static BrokenDatesGroup* parse(std::byte* buffer) {
        return reinterpret_cast<BrokenDatesGroup*>(buffer);
    }

    // parse method const
    static const BrokenDatesGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const BrokenDatesGroup*>(buffer);
    }
};

#pragma pack(pop)
}
