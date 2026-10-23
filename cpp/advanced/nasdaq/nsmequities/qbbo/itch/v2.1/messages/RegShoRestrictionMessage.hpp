#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/TimeStamp.hpp"
#include "../types/Stock.hpp"
#include "../types/RegShoAction.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

namespace itch_qbbo = ::nasdaq::nsmequities::qbbo::itch::v2_1;

#pragma pack(push, 1)

// Reg Sho Restriction Message
struct reg_sho_restriction_message {

    struct fields_type {
        itch_qbbo::tracking_number tracking_number;
        itch_qbbo::time_stamp time_stamp;
        itch_qbbo::stock stock;
        itch_qbbo::reg_sho_action reg_sho_action;
    };

    itch_qbbo::message_header header = {std::uint16_t(sizeof(itch_qbbo::message_header) + sizeof(fields_type) - 2), message_type::enum_type::reg_sho_restriction_message};

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
static_assert(offsetof(reg_sho_restriction_message::fields_type, tracking_number) == 0, "unexpected offset of reg_sho_restriction_message::fields_type::tracking_number");
static_assert(offsetof(reg_sho_restriction_message::fields_type, time_stamp) == 2, "unexpected offset of reg_sho_restriction_message::fields_type::time_stamp");
static_assert(offsetof(reg_sho_restriction_message::fields_type, stock) == 8, "unexpected offset of reg_sho_restriction_message::fields_type::stock");
static_assert(offsetof(reg_sho_restriction_message::fields_type, reg_sho_action) == 16, "unexpected offset of reg_sho_restriction_message::fields_type::reg_sho_action");
static_assert(sizeof(reg_sho_restriction_message::fields_type) == 17, "unexpected sizeof reg_sho_restriction_message::fields_type");
static_assert(sizeof(reg_sho_restriction_message) == sizeof(itch_qbbo::message_header) + 17, "unexpected sizeof reg_sho_restriction_message");

#pragma pack(pop)
}
