#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/TimeStamp.hpp"
#include "../types/BreachedLevel.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

namespace itch_qbbo = ::nasdaq::nsmequities::qbbo::itch::v2_1;

#pragma pack(push, 1)

// Mwcb Breach Message
struct mwcb_breach_message {

    struct fields_type {
        itch_qbbo::tracking_number tracking_number;
        itch_qbbo::time_stamp time_stamp;
        itch_qbbo::breached_level breached_level;
    };

    itch_qbbo::message_header header = {std::uint16_t(sizeof(itch_qbbo::message_header) + sizeof(fields_type) - 2), message_type::enum_type::mwcb_breach_message};

    fields_type fields;

    // parse method
    static mwcb_breach_message* parse(std::byte* buffer) {
        return reinterpret_cast<mwcb_breach_message*>(buffer);
    }

    // parse method const
    static const mwcb_breach_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const mwcb_breach_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(mwcb_breach_message::fields_type, tracking_number) == 0, "unexpected offset of mwcb_breach_message::fields_type::tracking_number");
static_assert(offsetof(mwcb_breach_message::fields_type, time_stamp) == 2, "unexpected offset of mwcb_breach_message::fields_type::time_stamp");
static_assert(offsetof(mwcb_breach_message::fields_type, breached_level) == 8, "unexpected offset of mwcb_breach_message::fields_type::breached_level");
static_assert(sizeof(mwcb_breach_message::fields_type) == 9, "unexpected sizeof mwcb_breach_message::fields_type");
static_assert(sizeof(mwcb_breach_message) == sizeof(itch_qbbo::message_header) + 9, "unexpected sizeof mwcb_breach_message");

#pragma pack(pop)
}
