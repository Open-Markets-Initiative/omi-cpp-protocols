#pragma once

#include "../types/StreamId.hpp"
#include "../types/Reserved2.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

#pragma pack(push, 1)

// In all multicast channels, a Stream ID Message is sent immediately after each packet header to uniquely identify the source or Stream ID of the data in the packet.
struct StreamIdMessage {

    StreamId stream_id;
    Reserved2 reserved_2;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 455;

    // parse method
    static StreamIdMessage* parse(std::byte* buffer) {
        return reinterpret_cast<StreamIdMessage*>(buffer);
    }

    // parse method const
    static const StreamIdMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const StreamIdMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const StreamIdMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const StreamIdMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
