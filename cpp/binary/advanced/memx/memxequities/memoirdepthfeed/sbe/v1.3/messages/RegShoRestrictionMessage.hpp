#pragma once

#include <cstddef>
#include "../structs/SbeHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/ShortSaleRestriction.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

namespace sbe_memoirdepthfeed = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

#pragma pack(push, 1)

// Reg Sho Restriction Message
struct reg_sho_restriction_message {

    struct fields_type {
        sbe_memoirdepthfeed::timestamp timestamp;
        sbe_memoirdepthfeed::security_id security_id;
        sbe_memoirdepthfeed::short_sale_restriction short_sale_restriction;
    };

    sbe_memoirdepthfeed::sbe_header header = {{}, template_id::enum_type::reg_sho_restriction_message, schema_id(2), version(259)};

    fields_type fields;

    // parse method
    static reg_sho_restriction_message* parse(std::byte* buffer) {
        return reinterpret_cast<reg_sho_restriction_message*>(buffer);
    }

    // parse method const
    static const reg_sho_restriction_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const reg_sho_restriction_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(reg_sho_restriction_message::fields_type, timestamp) == 0, "unexpected offset of reg_sho_restriction_message::fields_type::timestamp");
static_assert(offsetof(reg_sho_restriction_message::fields_type, security_id) == 8, "unexpected offset of reg_sho_restriction_message::fields_type::security_id");
static_assert(offsetof(reg_sho_restriction_message::fields_type, short_sale_restriction) == 10, "unexpected offset of reg_sho_restriction_message::fields_type::short_sale_restriction");
static_assert(sizeof(reg_sho_restriction_message::fields_type) == 11, "unexpected sizeof reg_sho_restriction_message::fields_type");
static_assert(sizeof(reg_sho_restriction_message) == sizeof(sbe_memoirdepthfeed::sbe_header) + 11, "unexpected sizeof reg_sho_restriction_message");

#pragma pack(pop)
}
