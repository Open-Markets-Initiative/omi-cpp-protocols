#pragma once

#include "../types/SourceId.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

#pragma pack(push, 1)

// Clients who remain connected to the Retransmission Server intraday must respond to a Heartbeat with a Heartbeat Response message within 5 seconds. If no timely client response is received, the connection will be closed.
struct HeartbeatResponseMessage {

    SourceId source_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 12;

    // parse method
    static HeartbeatResponseMessage* parse(std::byte* buffer) {
        return reinterpret_cast<HeartbeatResponseMessage*>(buffer);
    }

    // parse method const
    static const HeartbeatResponseMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const HeartbeatResponseMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const HeartbeatResponseMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const HeartbeatResponseMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
