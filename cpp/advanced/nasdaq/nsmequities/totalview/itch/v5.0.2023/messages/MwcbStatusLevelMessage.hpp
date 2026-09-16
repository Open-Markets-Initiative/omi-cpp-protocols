#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/BreachedLevel.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

#pragma pack(push, 1)

// Mwcb Status Level Message
struct mwcb_status_level_message {

    struct fields_type {
        itch_totalview::stock_locate stock_locate;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::timestamp timestamp;
        itch_totalview::breached_level breached_level;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::mwcb_status_level_message};

    fields_type fields;

    // parse method
    static mwcb_status_level_message* parse(std::byte* buffer) {
        return reinterpret_cast<mwcb_status_level_message*>(buffer);
    }

    // parse method const
    static const mwcb_status_level_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const mwcb_status_level_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(mwcb_status_level_message::fields_type, stock_locate) == 0, "unexpected offset of mwcb_status_level_message::fields_type::stock_locate");
static_assert(offsetof(mwcb_status_level_message::fields_type, tracking_number) == 2, "unexpected offset of mwcb_status_level_message::fields_type::tracking_number");
static_assert(offsetof(mwcb_status_level_message::fields_type, timestamp) == 4, "unexpected offset of mwcb_status_level_message::fields_type::timestamp");
static_assert(offsetof(mwcb_status_level_message::fields_type, breached_level) == 10, "unexpected offset of mwcb_status_level_message::fields_type::breached_level");
static_assert(sizeof(mwcb_status_level_message::fields_type) == 11, "unexpected sizeof mwcb_status_level_message::fields_type");
static_assert(sizeof(mwcb_status_level_message) == sizeof(message_header) + 11, "unexpected sizeof mwcb_status_level_message");

#pragma pack(pop)
}
