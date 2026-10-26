#pragma once

#include "../types/UserId.hpp"
#include "../types/MulticastGroupNumber.hpp"
#include "../types/NumberOfSystemReboots.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/RequestedMessageCount.hpp"
#include "../structs/TcpPacketHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

#pragma pack(push, 1)

// Tcp login request selecting snapshot, sent by the user. Same layout as the retransmission request; Number of System Reboots, Sequence Number and Requested Message Count are all set to 0.
struct LoginRequestSnapshotMessage {

    UserId user_id;
    MulticastGroupNumber multicast_group_number;
    NumberOfSystemReboots number_of_system_reboots;
    SequenceNumber sequence_number;
    RequestedMessageCount requested_message_count;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'L';

    // parse method
    static LoginRequestSnapshotMessage* parse(std::byte* buffer) {
        return reinterpret_cast<LoginRequestSnapshotMessage*>(buffer);
    }

    // parse method const
    static const LoginRequestSnapshotMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const LoginRequestSnapshotMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LoginRequestSnapshotMessage* parse(const TcpPacketHeader* header) {
        return reinterpret_cast<const LoginRequestSnapshotMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(TcpPacketHeader));
    }
};

#pragma pack(pop)
}
