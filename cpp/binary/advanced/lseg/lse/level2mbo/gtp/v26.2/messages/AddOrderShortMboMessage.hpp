#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/OrderId.hpp"
#include "../types/SizeType.hpp"
#include "../types/Price.hpp"
#include "../types/Reserved8.hpp"
#include "../types/Participant.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

namespace gtp_level2mbo = ::lseg::lse::level2mbo::gtp::v26_2;

#pragma pack(push, 1)

// Add Order Short Mbo Message
struct add_order_short_mbo_message {

    struct fields_type {
        gtp_level2mbo::order_id order_id;
        gtp_level2mbo::size_type size;
        gtp_level2mbo::price price;
        gtp_level2mbo::reserved_8 reserved_8;
        gtp_level2mbo::participant participant;
    };

    gtp_level2mbo::message_header header = {std::uint16_t(sizeof(gtp_level2mbo::message_header) + sizeof(fields_type)), message_type::enum_type::add_order_short_mbo_message};

    fields_type fields;

    // parse method
    static add_order_short_mbo_message* parse(std::byte* buffer) {
        return reinterpret_cast<add_order_short_mbo_message*>(buffer);
    }

    // parse method const
    static const add_order_short_mbo_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const add_order_short_mbo_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(add_order_short_mbo_message::fields_type, order_id) == 0, "unexpected offset of add_order_short_mbo_message::fields_type::order_id");
static_assert(offsetof(add_order_short_mbo_message::fields_type, size) == 8, "unexpected offset of add_order_short_mbo_message::fields_type::size");
static_assert(offsetof(add_order_short_mbo_message::fields_type, price) == 16, "unexpected offset of add_order_short_mbo_message::fields_type::price");
static_assert(offsetof(add_order_short_mbo_message::fields_type, reserved_8) == 24, "unexpected offset of add_order_short_mbo_message::fields_type::reserved_8");
static_assert(offsetof(add_order_short_mbo_message::fields_type, participant) == 32, "unexpected offset of add_order_short_mbo_message::fields_type::participant");
static_assert(sizeof(add_order_short_mbo_message::fields_type) == 43, "unexpected sizeof add_order_short_mbo_message::fields_type");
static_assert(sizeof(add_order_short_mbo_message) == sizeof(gtp_level2mbo::message_header) + 43, "unexpected sizeof add_order_short_mbo_message");

#pragma pack(pop)
}
