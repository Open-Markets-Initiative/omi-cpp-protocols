#pragma once

#include "../types/SequenceNumber.hpp"
#include "../structs/UnsequencedDataPacket.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

#pragma pack(push, 1)

// Sent by MIAX Options over the ToM Retransmission Interface (SesM Unsequenced Data Packet) carrying one Application Message that satisfies a previous Refresh Request. Note: MIAX Options PDF assigns Response Type "R" (uppercase) to this message, colliding with the Request Type "R" byte; lowercase "r" is used here to match the Pearl convention for case-distinct discrimination.
struct RefreshResponseMessage {

    SequenceNumber sequence_number;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'r';

    // parse method
    static RefreshResponseMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RefreshResponseMessage*>(buffer);
    }

    // parse method const
    static const RefreshResponseMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RefreshResponseMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RefreshResponseMessage* parse(const UnsequencedDataPacket* header) {
        return reinterpret_cast<const RefreshResponseMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(UnsequencedDataPacket));
    }
};

#pragma pack(pop)
}
