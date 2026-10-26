#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Text.hpp"

namespace cme::mdp3::v9 {

namespace sbe_mdp3 = ::cme::mdp3::v9;

#pragma pack(push, 1)

// Admin Logout
struct admin_logout {

    struct fields_type {
        sbe_mdp3::text text;
    };

    sbe_mdp3::message_header header = {std::uint16_t(sizeof(sbe_mdp3::message_header) + sizeof(fields_type)), {}};

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
static_assert(offsetof(admin_logout::fields_type, text) == 0, "unexpected offset of admin_logout::fields_type::text");
static_assert(sizeof(admin_logout::fields_type) == 100, "unexpected sizeof admin_logout::fields_type");
static_assert(sizeof(admin_logout) == sizeof(sbe_mdp3::message_header) + 100, "unexpected sizeof admin_logout");

#pragma pack(pop)
}
