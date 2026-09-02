#pragma once

#include "../types/IexTpHeader.hpp"
#include "../types/IexTpMessageBlockLength.hpp"
#include "../types/IexTpMessageLength.hpp"
#include "../types/IexTpMessageType.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

#pragma pack(push, 1)

// Carries one complete Tops feed message wrapped with an IexTp header providing Tops feed sequencing and timing information
struct SnapshotDataMessage {

    IexTpHeader iex_tp_header;
    IexTpMessageBlockLength iex_tp_message_block_length;
    IexTpMessageLength iex_tp_message_length;
    IexTpMessageType iex_tp_message_type;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'd';

    // parse method
    static SnapshotDataMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotDataMessage*>(buffer);
    }

    // parse method const
    static const SnapshotDataMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotDataMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SnapshotDataMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SnapshotDataMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
