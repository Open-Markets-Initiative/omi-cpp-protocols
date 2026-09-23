#pragma once

#include "../types/Username.hpp"
#include "../types/Password.hpp"
#include "../types/RequestedSession.hpp"
#include "../types/RequestedSequenceNumber.hpp"
#include "../structs/ClientPacketHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// The SoupBinTCP client must send a Login Request Packet immediately upon establishing a new TCP/IP socket connection to the server
struct LoginRequestPacket {

    Username username;
    Password password;
    RequestedSession requested_session;
    RequestedSequenceNumber requested_sequence_number;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'L';

    // parse method
    static LoginRequestPacket* parse(std::byte* buffer) {
        return reinterpret_cast<LoginRequestPacket*>(buffer);
    }

    // parse method const
    static const LoginRequestPacket* parse(const std::byte* buffer) {
        return reinterpret_cast<const LoginRequestPacket*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LoginRequestPacket* parse(const ClientPacketHeader* header) {
        return reinterpret_cast<const LoginRequestPacket*>(reinterpret_cast<const std::byte*>(header) + sizeof(ClientPacketHeader));
    }
};

#pragma pack(pop)
}
