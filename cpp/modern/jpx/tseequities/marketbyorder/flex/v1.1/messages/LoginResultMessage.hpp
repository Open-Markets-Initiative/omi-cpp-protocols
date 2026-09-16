#pragma once

#include "../types/MulticastGroupNumber.hpp"
#include "../types/ResultCode.hpp"
#include "../structs/TcpPacketHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

#pragma pack(push, 1)

// Tcp login response. Packet Type A indicates accepted and J indicates rejected.
struct LoginResultMessage {

    MulticastGroupNumber multicast_group_number;
    ResultCode result_code;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'A';

    // parse method
    static LoginResultMessage* parse(std::byte* buffer) {
        return reinterpret_cast<LoginResultMessage*>(buffer);
    }

    // parse method const
    static const LoginResultMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const LoginResultMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LoginResultMessage* parse(const TcpPacketHeader* header) {
        return reinterpret_cast<const LoginResultMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(TcpPacketHeader));
    }
};

#pragma pack(pop)
}
