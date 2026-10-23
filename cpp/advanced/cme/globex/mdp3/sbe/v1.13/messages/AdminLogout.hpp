#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/LogoutText.hpp"
#include "../types/MessageSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)

// Admin Logout
struct admin_logout {

    struct fields_type {
        sbe_mdp3::logout_text logout_text;
    };

    // Transport framing: message size precedes the SBE header on the wire
    sbe_mdp3::message_size message_size;
    sbe_mdp3::message_header header = {{}, template_id::enum_type::admin_logout, schema_id::enum_type::mktdata, version(13)};

    fields_type fields;

    // parse method
    static admin_logout* parse(std::byte* buffer) {
        return reinterpret_cast<admin_logout*>(buffer);
    }

    // parse method const
    static const admin_logout* parse(const std::byte* buffer) {
        return reinterpret_cast<const admin_logout*>(buffer);
    }

};

// layout verification
static_assert(offsetof(admin_logout::fields_type, logout_text) == 0, "unexpected offset of admin_logout::fields_type::logout_text");
static_assert(sizeof(admin_logout::fields_type) == 180, "unexpected sizeof admin_logout::fields_type");
static_assert(sizeof(admin_logout) == sizeof(sbe_mdp3::message_size) + sizeof(sbe_mdp3::message_header) + 180, "unexpected sizeof admin_logout");

#pragma pack(pop)
}
