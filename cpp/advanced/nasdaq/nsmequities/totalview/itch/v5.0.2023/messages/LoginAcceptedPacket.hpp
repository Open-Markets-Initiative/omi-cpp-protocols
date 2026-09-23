#pragma once

#include <cstddef>
#include "../structs/ServerPacketHeader.hpp"
#include "../types/AcceptedSession.hpp"
#include "../types/AcceptedSequenceNumber.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

#pragma pack(push, 1)

// Login Accepted Packet
struct login_accepted_packet {

    struct fields_type {
        itch_totalview::accepted_session accepted_session;
        itch_totalview::accepted_sequence_number accepted_sequence_number;
    };

    server_packet_header header = {std::uint16_t(sizeof(server_packet_header) + sizeof(fields_type) - 2), server_packet_type::enum_type::login_accepted_packet};

    fields_type fields;

    // parse method
    static login_accepted_packet* parse(std::byte* buffer) {
        return reinterpret_cast<login_accepted_packet*>(buffer);
    }

    // parse method const
    static const login_accepted_packet* parse(const std::byte* buffer) {
        return reinterpret_cast<const login_accepted_packet*>(buffer);
    }

};

// layout verification
static_assert(offsetof(login_accepted_packet::fields_type, accepted_session) == 0, "unexpected offset of login_accepted_packet::fields_type::accepted_session");
static_assert(offsetof(login_accepted_packet::fields_type, accepted_sequence_number) == 10, "unexpected offset of login_accepted_packet::fields_type::accepted_sequence_number");
static_assert(sizeof(login_accepted_packet::fields_type) == 30, "unexpected sizeof login_accepted_packet::fields_type");
static_assert(sizeof(login_accepted_packet) == sizeof(server_packet_header) + 30, "unexpected sizeof login_accepted_packet");

#pragma pack(pop)
}
