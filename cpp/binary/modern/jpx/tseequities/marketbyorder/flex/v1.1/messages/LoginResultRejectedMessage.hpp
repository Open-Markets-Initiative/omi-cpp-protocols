#pragma once

#include "../types/MulticastGroupNumber.hpp"
#include "../types/ResultCode.hpp"
#include "../structs/TcpPacketHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

#pragma pack(push, 1)

// Tcp login response rejecting the request. Same layout as the accepted response; Result Code carries the reason the request failed.
struct LoginResultRejectedMessage {

    MulticastGroupNumber multicast_group_number;
    ResultCode result_code;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'J';

    // parse method
    static LoginResultRejectedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<LoginResultRejectedMessage*>(buffer);
    }

    // parse method const
    static const LoginResultRejectedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const LoginResultRejectedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LoginResultRejectedMessage* parse(const TcpPacketHeader* header) {
        return reinterpret_cast<const LoginResultRejectedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(TcpPacketHeader));
    }
};

#pragma pack(pop)
}
