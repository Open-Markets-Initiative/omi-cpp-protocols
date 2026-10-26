#pragma once

#include "../types/MulticastGroupNumber.hpp"
#include "../types/ResultCode.hpp"
#include "../structs/TcpPacketHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

#pragma pack(push, 1)

// Tcp login response accepting the request. Result Code carries A.
struct LoginResultAcceptedMessage {

    MulticastGroupNumber multicast_group_number;
    ResultCode result_code;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'A';

    // parse method
    static LoginResultAcceptedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<LoginResultAcceptedMessage*>(buffer);
    }

    // parse method const
    static const LoginResultAcceptedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const LoginResultAcceptedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LoginResultAcceptedMessage* parse(const TcpPacketHeader* header) {
        return reinterpret_cast<const LoginResultAcceptedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(TcpPacketHeader));
    }
};

#pragma pack(pop)
}
