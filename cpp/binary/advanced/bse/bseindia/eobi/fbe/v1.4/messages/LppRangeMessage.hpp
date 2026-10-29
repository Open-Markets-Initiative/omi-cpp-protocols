#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/UpperExecLimit.hpp"
#include "../types/LowerExecLimit.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

namespace fbe_eobi = ::bse::bseindia::eobi::fbe::v1_4;

#pragma pack(push, 1)

// Lpp Range Message
struct lpp_range_message {

    struct fields_type {
        fbe_eobi::security_id security_id;
        fbe_eobi::upper_exec_limit upper_exec_limit;
        fbe_eobi::lower_exec_limit lower_exec_limit;
    };

    fbe_eobi::message_header header = {std::uint16_t(sizeof(fbe_eobi::message_header) + sizeof(fields_type)), template_id::enum_type::lpp_range_message, {}};

    fields_type fields;

    // parse method
    static lpp_range_message* parse(std::byte* buffer) {
        return reinterpret_cast<lpp_range_message*>(buffer);
    }

    // parse method const
    static const lpp_range_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const lpp_range_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(lpp_range_message::fields_type, security_id) == 0, "unexpected offset of lpp_range_message::fields_type::security_id");
static_assert(offsetof(lpp_range_message::fields_type, upper_exec_limit) == 8, "unexpected offset of lpp_range_message::fields_type::upper_exec_limit");
static_assert(offsetof(lpp_range_message::fields_type, lower_exec_limit) == 16, "unexpected offset of lpp_range_message::fields_type::lower_exec_limit");
static_assert(sizeof(lpp_range_message::fields_type) == 24, "unexpected sizeof lpp_range_message::fields_type");
static_assert(sizeof(lpp_range_message) == sizeof(fbe_eobi::message_header) + 24, "unexpected sizeof lpp_range_message");

#pragma pack(pop)
}
