#pragma once

#include <cstddef>
#include "../types/Session.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/MessageCount.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2026;

#pragma pack(push, 1)

struct packet_header {

    itch_totalview::session session;
    itch_totalview::sequence_number sequence_number;
    itch_totalview::message_count message_count;

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
