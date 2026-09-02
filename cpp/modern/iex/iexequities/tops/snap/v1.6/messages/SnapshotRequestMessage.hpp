#pragma once

#include "../types/AuthenticationToken.hpp"
#include "../types/ChannelId.hpp"
#include "../types/SessionId.hpp"
#include "../types/MinimumSequenceNumber.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

#pragma pack(push, 1)

// The Snapshot Request message is sent from the client to the Tops Snap server to authenticate and request a Snapshot Response
struct SnapshotRequestMessage {

    AuthenticationToken authentication_token;
    ChannelId channel_id;
    SessionId session_id;
    MinimumSequenceNumber minimum_sequence_number;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'r';

    // parse method
    static SnapshotRequestMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotRequestMessage*>(buffer);
    }

    // parse method const
    static const SnapshotRequestMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotRequestMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SnapshotRequestMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SnapshotRequestMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
