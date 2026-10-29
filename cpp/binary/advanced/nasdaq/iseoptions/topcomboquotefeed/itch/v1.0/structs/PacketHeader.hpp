#pragma once

#include <cstddef>
#include "../types/Session.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/MessageCount.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

namespace itch_topcomboquotefeed = ::nasdaq::iseoptions::topcomboquotefeed::itch::v1_0;

#pragma pack(push, 1)

struct packet_header {

    itch_topcomboquotefeed::session session;
    itch_topcomboquotefeed::sequence_number sequence_number;
    itch_topcomboquotefeed::message_count message_count;

    // parse method
    static packet_header* parse(std::byte* buffer) {
        return reinterpret_cast<packet_header*>(buffer);
    }

    // parse method const
    static const packet_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const packet_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(packet_header, session) == 0, "unexpected offset of packet_header::session");
static_assert(offsetof(packet_header, sequence_number) == 10, "unexpected offset of packet_header::sequence_number");
static_assert(offsetof(packet_header, message_count) == 18, "unexpected offset of packet_header::message_count");
static_assert(sizeof(packet_header) == 20, "unexpected sizeof packet_header");

#pragma pack(pop)
}
