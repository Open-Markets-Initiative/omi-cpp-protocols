#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/MessageSize.hpp"

namespace cme::mdp3::v8 {

namespace sbe_mdp3 = ::cme::mdp3::v8;

#pragma pack(push, 1)

// Admin Heartbeat
struct admin_heartbeat {

    // Transport framing: message size precedes the SBE header on the wire
    sbe_mdp3::message_size message_size;
    sbe_mdp3::message_header header = {{}, template_id::enum_type::admin_heartbeat, schema_id::enum_type::mktdata, version(8)};

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
static_assert(sizeof(admin_heartbeat) == sizeof(sbe_mdp3::message_size) + sizeof(sbe_mdp3::message_header) + 0, "unexpected sizeof admin_heartbeat");

#pragma pack(pop)
}
