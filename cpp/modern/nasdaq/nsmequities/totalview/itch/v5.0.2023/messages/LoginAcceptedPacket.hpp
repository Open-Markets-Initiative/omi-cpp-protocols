#pragma once

#include "../types/AcceptedSession.hpp"
#include "../types/AcceptedSequenceNumber.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// The SoupBinTCP server sends a Login Accepted Packet in response to receiving a valid Login Request from the client
struct LoginAcceptedPacket {

    AcceptedSession accepted_session;
    AcceptedSequenceNumber accepted_sequence_number;

    // parse method
    static LoginAcceptedPacket* parse(std::byte* buffer) {
        return reinterpret_cast<LoginAcceptedPacket*>(buffer);
    }

    // parse method const
    static const LoginAcceptedPacket* parse(const std::byte* buffer) {
        return reinterpret_cast<const LoginAcceptedPacket*>(buffer);
    }
};

#pragma pack(pop)
}
