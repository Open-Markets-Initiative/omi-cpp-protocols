#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/OrderDetails.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

namespace fbe_eobi = ::bse::bseindia::eobi::fbe::v1_4;

#pragma pack(push, 1)

// Snapshot Order Message
struct snapshot_order_message {

    struct fields_type {
        fbe_eobi::order_details order_details;
    };

    fbe_eobi::message_header header = {std::uint16_t(sizeof(fbe_eobi::message_header) + sizeof(fields_type)), template_id::enum_type::snapshot_order_message, {}};

    fields_type fields;

    // parse method
    static snapshot_order_message* parse(std::byte* buffer) {
        return reinterpret_cast<snapshot_order_message*>(buffer);
    }

    // parse method const
    static const snapshot_order_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const snapshot_order_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(snapshot_order_message::fields_type, order_details) == 0, "unexpected offset of snapshot_order_message::fields_type::order_details");
static_assert(sizeof(snapshot_order_message::fields_type) == 32, "unexpected sizeof snapshot_order_message::fields_type");
static_assert(sizeof(snapshot_order_message) == sizeof(fbe_eobi::message_header) + 32, "unexpected sizeof snapshot_order_message");

#pragma pack(pop)
}
