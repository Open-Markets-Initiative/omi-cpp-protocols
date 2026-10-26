#pragma once

#include "../types/RefreshMessageType.hpp"
#include "../structs/UnsequencedDataPacket.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

#pragma pack(push, 1)

// Sent by MIAX Options over the ToM Retransmission Interface (SesM Unsequenced Data Packet) when the refresh response is complete.
struct EndOfRefreshNotificationMessage {

    RefreshMessageType refresh_message_type;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'E';

    // parse method
    static EndOfRefreshNotificationMessage* parse(std::byte* buffer) {
        return reinterpret_cast<EndOfRefreshNotificationMessage*>(buffer);
    }

    // parse method const
    static const EndOfRefreshNotificationMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const EndOfRefreshNotificationMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const EndOfRefreshNotificationMessage* parse(const UnsequencedDataPacket* header) {
        return reinterpret_cast<const EndOfRefreshNotificationMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(UnsequencedDataPacket));
    }
};

#pragma pack(pop)
}
