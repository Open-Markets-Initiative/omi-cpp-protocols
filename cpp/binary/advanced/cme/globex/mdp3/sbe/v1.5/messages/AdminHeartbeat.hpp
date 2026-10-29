#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"

namespace cme::mdp3::v5 {

namespace sbe_mdp3 = ::cme::mdp3::v5;

#pragma pack(push, 1)

// Admin Heartbeat
struct admin_heartbeat {

    sbe_mdp3::message_header header = {std::uint16_t(sizeof(sbe_mdp3::message_header)), {}};

    // parse method
    static admin_heartbeat* parse(std::byte* buffer) {
        return reinterpret_cast<admin_heartbeat*>(buffer);
    }

    // parse method const
    static const admin_heartbeat* parse(const std::byte* buffer) {
        return reinterpret_cast<const admin_heartbeat*>(buffer);
    }

};

// layout verification
static_assert(sizeof(admin_heartbeat) == sizeof(sbe_mdp3::message_header) + 0, "unexpected sizeof admin_heartbeat");

#pragma pack(pop)
}
