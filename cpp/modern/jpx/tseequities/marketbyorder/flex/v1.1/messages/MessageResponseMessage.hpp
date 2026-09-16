#pragma once

#include "../types/Data.hpp"
#include "../structs/TcpPacketHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

#pragma pack(push, 1)

// Tcp message response carrying tag data including their packet headers in response to a retransmission or snapshot request.
struct MessageResponseMessage {

    Data data;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'S';

    // parse method
    static MessageResponseMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MessageResponseMessage*>(buffer);
    }

    // parse method const
    static const MessageResponseMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MessageResponseMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MessageResponseMessage* parse(const TcpPacketHeader* header) {
        return reinterpret_cast<const MessageResponseMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(TcpPacketHeader));
    }
};

#pragma pack(pop)
}
