#pragma once

#include "../types/RefreshMessageType.hpp"
#include "../structs/UnsequencedDataPacket.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

#pragma pack(push, 1)

// Sent by the firm over the ToM Retransmission Interface (SesM Unsequenced Data Packet) to request a Last Value Refresh of a particular data set identified by Refresh Message Type.
struct RefreshRequestMessage {

    RefreshMessageType refresh_message_type;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'R';

    // parse method
    static RefreshRequestMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RefreshRequestMessage*>(buffer);
    }

    // parse method const
    static const RefreshRequestMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RefreshRequestMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RefreshRequestMessage* parse(const UnsequencedDataPacket* header) {
        return reinterpret_cast<const RefreshRequestMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(UnsequencedDataPacket));
    }
};

#pragma pack(pop)
}
