#pragma once

#include "../types/SnapshotSequenceNumber.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

#pragma pack(push, 1)

// Final message of a Snapshot Response, carries the sequence number at which the snapshot was created
struct SnapshotEndMessage {

    SnapshotSequenceNumber snapshot_sequence_number;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'x';

    // parse method
    static SnapshotEndMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotEndMessage*>(buffer);
    }

    // parse method const
    static const SnapshotEndMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotEndMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SnapshotEndMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SnapshotEndMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
