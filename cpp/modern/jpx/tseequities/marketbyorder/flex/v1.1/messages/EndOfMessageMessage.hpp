#pragma once

#include "../types/MulticastGroupNumber.hpp"
#include "../types/NumberOfSystemReboots.hpp"
#include "../types/NextSequenceNumber.hpp"
#include "../structs/TcpPacketHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

#pragma pack(push, 1)

// Tcp end of message marker terminating a retransmission or snapshot session.
struct EndOfMessageMessage {

    MulticastGroupNumber multicast_group_number;
    NumberOfSystemReboots number_of_system_reboots;
    NextSequenceNumber next_sequence_number;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'G';

    // parse method
    static EndOfMessageMessage* parse(std::byte* buffer) {
        return reinterpret_cast<EndOfMessageMessage*>(buffer);
    }

    // parse method const
    static const EndOfMessageMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const EndOfMessageMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const EndOfMessageMessage* parse(const TcpPacketHeader* header) {
        return reinterpret_cast<const EndOfMessageMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(TcpPacketHeader));
    }
};

#pragma pack(pop)
}
