#pragma once

#include "../types/Custodian.hpp"
#include "../types/CustodyAccount.hpp"
#include "../types/CustodyAllocationType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

struct CustodianInfo {

    Custodian custodian;
    CustodyAccount custody_account;
    CustodyAllocationType custody_allocation_type;

    // parse method
    static CustodianInfo* parse(std::byte* buffer) {
        return reinterpret_cast<CustodianInfo*>(buffer);
    }

    // parse method const
    static const CustodianInfo* parse(const std::byte* buffer) {
        return reinterpret_cast<const CustodianInfo*>(buffer);
    }
};

#pragma pack(pop)
}
