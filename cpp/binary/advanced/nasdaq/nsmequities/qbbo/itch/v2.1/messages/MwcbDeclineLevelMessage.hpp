#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/TimeStamp.hpp"
#include "../types/Level1.hpp"
#include "../types/Level2.hpp"
#include "../types/Level3.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

namespace itch_qbbo = ::nasdaq::nsmequities::qbbo::itch::v2_1;

#pragma pack(push, 1)

// Mwcb Decline Level Message
struct mwcb_decline_level_message {

    struct fields_type {
        itch_qbbo::tracking_number tracking_number;
        itch_qbbo::time_stamp time_stamp;
        itch_qbbo::level_1 level_1;
        itch_qbbo::level_2 level_2;
        itch_qbbo::level_3 level_3;
    };

    itch_qbbo::message_header header = {std::uint16_t(sizeof(itch_qbbo::message_header) + sizeof(fields_type) - 2), message_type::enum_type::mwcb_decline_level_message};

    fields_type fields;

    // parse method
    static mwcb_decline_level_message* parse(std::byte* buffer) {
        return reinterpret_cast<mwcb_decline_level_message*>(buffer);
    }

    // parse method const
    static const mwcb_decline_level_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const mwcb_decline_level_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(mwcb_decline_level_message::fields_type, tracking_number) == 0, "unexpected offset of mwcb_decline_level_message::fields_type::tracking_number");
static_assert(offsetof(mwcb_decline_level_message::fields_type, time_stamp) == 2, "unexpected offset of mwcb_decline_level_message::fields_type::time_stamp");
static_assert(offsetof(mwcb_decline_level_message::fields_type, level_1) == 8, "unexpected offset of mwcb_decline_level_message::fields_type::level_1");
static_assert(offsetof(mwcb_decline_level_message::fields_type, level_2) == 16, "unexpected offset of mwcb_decline_level_message::fields_type::level_2");
static_assert(offsetof(mwcb_decline_level_message::fields_type, level_3) == 24, "unexpected offset of mwcb_decline_level_message::fields_type::level_3");
static_assert(sizeof(mwcb_decline_level_message::fields_type) == 32, "unexpected sizeof mwcb_decline_level_message::fields_type");
static_assert(sizeof(mwcb_decline_level_message) == sizeof(itch_qbbo::message_header) + 32, "unexpected sizeof mwcb_decline_level_message");

#pragma pack(pop)
}
