#pragma once

#include "../types/Transaction.hpp"
#include "../types/Reserved3.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

#pragma pack(push, 1)

struct CorrectionCondition {

    Transaction transaction;
    Reserved3 reserved_3;

    // parse method
    static CorrectionCondition* parse(std::byte* buffer) {
        return reinterpret_cast<CorrectionCondition*>(buffer);
    }

    // parse method const
    static const CorrectionCondition* parse(const std::byte* buffer) {
        return reinterpret_cast<const CorrectionCondition*>(buffer);
    }
};

#pragma pack(pop)
}
