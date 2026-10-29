#pragma once

#include <cstddef>
#include "../types/Custodian.hpp"
#include "../types/CustodyAccount.hpp"
#include "../types/CustodyAllocationType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;

#pragma pack(push, 1)

struct custodian_info {

    sbe_binaryentrypoint::custodian custodian;
    sbe_binaryentrypoint::custody_account custody_account;
    sbe_binaryentrypoint::custody_allocation_type custody_allocation_type;

    // parse method
    static custodian_info* parse(std::byte* buffer) {
        return reinterpret_cast<custodian_info*>(buffer);
    }

    // parse method const
    static const custodian_info* parse(const std::byte* buffer) {
        return reinterpret_cast<const custodian_info*>(buffer);
    }
};

// layout verification
static_assert(offsetof(custodian_info, custodian) == 0, "unexpected offset of custodian_info::custodian");
static_assert(offsetof(custodian_info, custody_account) == 4, "unexpected offset of custodian_info::custody_account");
static_assert(offsetof(custodian_info, custody_allocation_type) == 8, "unexpected offset of custodian_info::custody_allocation_type");
static_assert(sizeof(custodian_info) == 12, "unexpected sizeof custodian_info");

#pragma pack(pop)
}
