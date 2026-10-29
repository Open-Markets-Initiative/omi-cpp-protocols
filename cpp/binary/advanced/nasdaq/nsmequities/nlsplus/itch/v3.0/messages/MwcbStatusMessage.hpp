#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/BreachedLevel.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

// Mwcb Status Message
struct mwcb_status_message {

    struct fields_type {
        itch_nlsplus::breached_level breached_level;
    };

    itch_nlsplus::message_header header = {std::uint16_t(sizeof(itch_nlsplus::message_header) + sizeof(fields_type) - 2), {}, {}, message_type::enum_type::mwcb_status_message};

    fields_type fields;

    // parse method
    static mwcb_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<mwcb_status_message*>(buffer);
    }

    // parse method const
    static const mwcb_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const mwcb_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(mwcb_status_message::fields_type, breached_level) == 0, "unexpected offset of mwcb_status_message::fields_type::breached_level");
static_assert(sizeof(mwcb_status_message::fields_type) == 1, "unexpected sizeof mwcb_status_message::fields_type");
static_assert(sizeof(mwcb_status_message) == sizeof(itch_nlsplus::message_header) + 1, "unexpected sizeof mwcb_status_message");

#pragma pack(pop)
}
