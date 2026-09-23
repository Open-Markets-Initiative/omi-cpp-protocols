#pragma once

#include <cstddef>
#include "../structs/ClientPacketHeader.hpp"
#include "../types/Username.hpp"
#include "../types/Password.hpp"
#include "../types/RequestedSession.hpp"
#include "../types/RequestedSequenceNumber.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

#pragma pack(push, 1)

// Login Request Packet
struct login_request_packet {

    struct fields_type {
        itch_totalview::username username;
        itch_totalview::password password;
        itch_totalview::requested_session requested_session;
        itch_totalview::requested_sequence_number requested_sequence_number;
    };

    client_packet_header header = {std::uint16_t(sizeof(client_packet_header) + sizeof(fields_type) - 2), client_packet_type::enum_type::login_request_packet};

    fields_type fields;

    // parse method
    static login_request_packet* parse(std::byte* buffer) {
        return reinterpret_cast<login_request_packet*>(buffer);
    }

    // parse method const
    static const login_request_packet* parse(const std::byte* buffer) {
        return reinterpret_cast<const login_request_packet*>(buffer);
    }

};

// layout verification
static_assert(offsetof(login_request_packet::fields_type, username) == 0, "unexpected offset of login_request_packet::fields_type::username");
static_assert(offsetof(login_request_packet::fields_type, password) == 6, "unexpected offset of login_request_packet::fields_type::password");
static_assert(offsetof(login_request_packet::fields_type, requested_session) == 16, "unexpected offset of login_request_packet::fields_type::requested_session");
static_assert(offsetof(login_request_packet::fields_type, requested_sequence_number) == 26, "unexpected offset of login_request_packet::fields_type::requested_sequence_number");
static_assert(sizeof(login_request_packet::fields_type) == 46, "unexpected sizeof login_request_packet::fields_type");
static_assert(sizeof(login_request_packet) == sizeof(client_packet_header) + 46, "unexpected sizeof login_request_packet");

#pragma pack(pop)
}
