#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/TransactTime.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v13_0;

#pragma pack(push, 1)

// Order Mass Delete
struct order_mass_delete {

    struct fields_type {
        fbe_eobi::security_id security_id;
        fbe_eobi::transact_time transact_time;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::order_mass_delete, {}};

    fields_type fields;

    // parse method
    static order_mass_delete* parse(std::byte* buffer) {
        return reinterpret_cast<order_mass_delete*>(buffer);
    }

    // parse method const
    static const order_mass_delete* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_mass_delete*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_mass_delete::fields_type, security_id) == 0, "unexpected offset of order_mass_delete::fields_type::security_id");
static_assert(offsetof(order_mass_delete::fields_type, transact_time) == 8, "unexpected offset of order_mass_delete::fields_type::transact_time");
static_assert(sizeof(order_mass_delete::fields_type) == 16, "unexpected sizeof order_mass_delete::fields_type");
static_assert(sizeof(order_mass_delete) == sizeof(fbe_eobi::message_header_comp) + 16, "unexpected sizeof order_mass_delete");

#pragma pack(pop)
}
