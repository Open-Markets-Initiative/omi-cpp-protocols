#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"

namespace cme::mdp3::v8 {

namespace sbe_mdp3 = ::cme::mdp3::v8;

#pragma pack(push, 1)

// Subscriber Heartbeat
struct subscriber_heartbeat {

    sbe_mdp3::message_header header = {std::uint16_t(sizeof(sbe_mdp3::message_header)), {}};

    // parse method
    static subscriber_heartbeat* parse(std::byte* buffer) {
        return reinterpret_cast<subscriber_heartbeat*>(buffer);
    }

    // parse method const
    static const subscriber_heartbeat* parse(const std::byte* buffer) {
        return reinterpret_cast<const subscriber_heartbeat*>(buffer);
    }

};

// layout verification
static_assert(sizeof(subscriber_heartbeat) == sizeof(sbe_mdp3::message_header) + 0, "unexpected sizeof subscriber_heartbeat");

#pragma pack(pop)
}
