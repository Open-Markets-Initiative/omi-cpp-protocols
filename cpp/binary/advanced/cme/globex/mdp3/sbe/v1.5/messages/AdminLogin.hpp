#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/HeartBtInt.hpp"

namespace cme::mdp3::v5 {

namespace sbe_mdp3 = ::cme::mdp3::v5;

#pragma pack(push, 1)

// Admin Login
struct admin_login {

    struct fields_type {
        sbe_mdp3::heart_bt_int heart_bt_int;
    };

    sbe_mdp3::message_header header = {std::uint16_t(sizeof(sbe_mdp3::message_header) + sizeof(fields_type)), {}};

    fields_type fields;

    // parse method
    static admin_login* parse(std::byte* buffer) {
        return reinterpret_cast<admin_login*>(buffer);
    }

    // parse method const
    static const admin_login* parse(const std::byte* buffer) {
        return reinterpret_cast<const admin_login*>(buffer);
    }

};

// layout verification
static_assert(offsetof(admin_login::fields_type, heart_bt_int) == 0, "unexpected offset of admin_login::fields_type::heart_bt_int");
static_assert(sizeof(admin_login::fields_type) == 1, "unexpected sizeof admin_login::fields_type");
static_assert(sizeof(admin_login) == sizeof(sbe_mdp3::message_header) + 1, "unexpected sizeof admin_login");

#pragma pack(pop)
}
