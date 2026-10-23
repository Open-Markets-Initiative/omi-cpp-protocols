#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../structs/OrderDetailsComp.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v15_0;

#pragma pack(push, 1)

// Snapshot Order
struct snapshot_order {

    struct fields_type {
        fbe_eobi::order_details_comp order_details_comp;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::snapshot_order, {}};

    fields_type fields;

    // parse method
    static snapshot_order* parse(std::byte* buffer) {
        return reinterpret_cast<snapshot_order*>(buffer);
    }

    // parse method const
    static const snapshot_order* parse(const std::byte* buffer) {
        return reinterpret_cast<const snapshot_order*>(buffer);
    }

};

// layout verification
static_assert(offsetof(snapshot_order::fields_type, order_details_comp) == 0, "unexpected offset of snapshot_order::fields_type::order_details_comp");
static_assert(sizeof(snapshot_order::fields_type) == 32, "unexpected sizeof snapshot_order::fields_type");
static_assert(sizeof(snapshot_order) == sizeof(fbe_eobi::message_header_comp) + 32, "unexpected sizeof snapshot_order");

#pragma pack(pop)
}
