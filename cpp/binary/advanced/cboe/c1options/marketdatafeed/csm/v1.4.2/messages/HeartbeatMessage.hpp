#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

#pragma pack(push, 1)

// Heartbeat Message
struct heartbeat_message {

    csm_marketdatafeed::message_header header = {{}, template_id::enum_type::heartbeat_message, {}, {}};

    // parse method
    static heartbeat_message* parse(std::byte* buffer) {
        return reinterpret_cast<heartbeat_message*>(buffer);
    }

    // parse method const
    static const heartbeat_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const heartbeat_message*>(buffer);
    }

};

// layout verification
static_assert(sizeof(heartbeat_message) == sizeof(csm_marketdatafeed::message_header) + 0, "unexpected sizeof heartbeat_message");

#pragma pack(pop)
}
