#pragma once

#include "../types/Username.hpp"
#include "../types/Password.hpp"
#include "../types/RequestedSession.hpp"
#include "../types/RequestedSequenceNumber.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

#pragma pack(push, 1)

// The SoupBinTCP client must send a Login Request Packet immediately upon establishing a new TCP/IP socket connection to the server
struct LoginRequestPacket {

    Username username;
    Password password;
    RequestedSession requested_session;
    RequestedSequenceNumber requested_sequence_number;

    // parse method
    static LoginRequestPacket* parse(std::byte* buffer) {
        return reinterpret_cast<LoginRequestPacket*>(buffer);
    }

    // parse method const
    static const LoginRequestPacket* parse(const std::byte* buffer) {
        return reinterpret_cast<const LoginRequestPacket*>(buffer);
    }
};

#pragma pack(pop)
}
