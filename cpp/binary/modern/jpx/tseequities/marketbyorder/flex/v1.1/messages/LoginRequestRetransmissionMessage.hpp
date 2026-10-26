#pragma once

#include "../types/UserId.hpp"
#include "../types/MulticastGroupNumber.hpp"
#include "../types/NumberOfSystemReboots.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/RequestedMessageCount.hpp"
#include "../structs/TcpPacketHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

#pragma pack(push, 1)

// Tcp login request selecting retransmission, sent by the user. One of the two Packet Type codes the document gives the 18 byte Login Request.
struct LoginRequestRetransmissionMessage {

    UserId user_id;
    MulticastGroupNumber multicast_group_number;
    NumberOfSystemReboots number_of_system_reboots;
    SequenceNumber sequence_number;
    RequestedMessageCount requested_message_count;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'R';

    // parse method
    static LoginRequestRetransmissionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<LoginRequestRetransmissionMessage*>(buffer);
    }

    // parse method const
    static const LoginRequestRetransmissionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const LoginRequestRetransmissionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LoginRequestRetransmissionMessage* parse(const TcpPacketHeader* header) {
        return reinterpret_cast<const LoginRequestRetransmissionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(TcpPacketHeader));
    }
};

#pragma pack(pop)
}
